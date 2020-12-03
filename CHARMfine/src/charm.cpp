/* 

 g++ -I/usr/local/include/eigen3 -o diag diag.cpp

*/

#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <libgen.h>
#include "QatPlotting/PlotPoint.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"


#include <iostream>
#include <Eigen/Eigenvalues> 
      
using namespace std;
using namespace Eigen;

double a = 0.546;
double b = 0.143;
double m = 1.48;
double sig = 1.095;


double V(double x) {
   return -4*a/(3*x)+b*(x);
}
double V_hyp(double x,double s){
  return 0.6565*exp(-sig*sig*x*x)*(s*(s+1)-0.75)/2;
}
double V_fin(double x, double s, double l, double j){
  if (l ==0 | s == 0){
    return (2*a/x/x/x-b/(2*x))*1/(m*m)*(j*(j+1)-l*(l+1)-s*(s+1))/2;
  }
  else {
  if (j == l){
    return (2*a/x/x/x-b/(2*x))*1/(m*m)*(j*(j+1)-l*(l+1)-s*(s+1))/2 
    +4*a/x/x/x*1/(m*m)*1./6;
  }
  else if (j == l-1){
    return (2*a/x/x/x-b/(2*x))*1/(m*m)*(j*(j+1)-l*(l+1)-s*(s+1))/2 
    -4*a/x/x/x*1/(m*m)*(l+1.)/(6*(2*l-1));
  }
  else if (j == l+1){
    return (2*a/x/x/x-b/(2*x))*1/(m*m)*(j*(j+1)-l*(l+1)-s*(s+1))/2 
    -4*a/x/x/x*1/(m*m)*(l)/(6*(2.*l+3.));
  }
  else{
    return (2*a/x/x/x-b/(2*x))*1/(m*m)*(j*(j+1)-l*(l+1)-s*(s+1))/2;
  }
  }
}



MatrixXd En(int N,double ell, double s, double dx, double j){
    MatrixXd H = MatrixXd::Zero(N,N); // variable-size double matrix
  // fill in H
  for (int i=0;i<N;i++) {
    double x = i*dx + dx;
    H(i,i) = 1/m* (2/(dx*dx) + ell*(ell+1.0)/(x*x))+ V(x) + V_hyp(x,s)+V_fin(x,s,ell,j);
    // cout<<V(x)<<endl;
  }
  for (int i=0;i<N-1;i++) {
    H(i,i+1) = -1/m/(dx*dx) ;
    H(i+1,i) = -1/m/(dx*dx) ;
  }
  return H;
}

int main (int argc, char **argv) {
  int N=500;
  double xmax = 15;
  double dx = xmax/N;


  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax(20);
  rect.setYmin(-3);
  rect.setYmax(3);
  
 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);

  PlotProfile prof;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("blue");
    prop.brush.setStyle(Qt::SolidPattern);
    prof.setProperties(prop);
  }
 PlotProfile prof2;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("red");
    prop.brush.setStyle(Qt::SolidPattern);
    prof2.setProperties(prop);
  }


  
  using namespace Genfun;
 
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "r[GeV^-1]"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "\u03A8"
	       << PlotStream::EndP();
  



  for (double l =0; l<=2; l++){
    for (double s = 0;s<=1;s++){
      for (double j =abs(l-s);j<=abs(l+s);j++){
        if((l==2&j==1)|(l<2)){
        MatrixXd H = En(N,l,s,dx,j);
        SelfAdjointEigenSolver<MatrixXd> es(H);   
        VectorXd ev0(N),ev1(N);
        ev0 = es.eigenvectors().col(0).normalized();  // ith eigenvector
        ev0 /= sqrt(dx);  
        ev1 = es.eigenvectors().col(1).normalized();  // ith eigenvector
        ev1 /= sqrt(dx);                     // normalize
        cout << "N = 1, L = "<<l<<", S = "<<s<<", J = "<<j<<",  mass = "<<es.eigenvalues()[0] +2.96<<"GeV" << endl;
        cout << "N = 2, L = "<<l<<", S = "<<s<<", J = "<<j<<",  mass = "<<es.eigenvalues()[1] +2.96<<"GeV" << endl;
       
        // for(unsigned int i =0;i<ev0.size();i++){
        // prof.addPoint(i*dx,ev0(i));
        // prof2.addPoint(i*dx,ev1(i));

      }



        
  
       
       
        }
      }
    }
  }


  // MatrixXd H = En(N,ell,s,dx,0);
  // SelfAdjointEigenSolver<MatrixXd> es(H);   
  // VectorXd ev0(N),ev1(N);
  //   ev0 = es.eigenvectors().col(0).normalized();  // ith eigenvector
  //   ev0 /= sqrt(dx);  
  //   ev1 = es.eigenvectors().col(1).normalized();  // ith eigenvector
  //   ev1 /= sqrt(dx);      
  //   // cout<<ev<<endl;                       // normalize
  //   cout << "N = 1, L = 0, S = 0, J = 0, mass = "<<es.eigenvalues()[0] +2.96<<"GeV" << endl;
  //   cout << "N = 2, L = 0, S = 0, J = 0, mass = "<<es.eigenvalues()[1] +2.96 <<"GeV"<< endl;
  // s=s+1;
  // MatrixXd H1 = En(N,ell,1,dx,1);
  // SelfAdjointEigenSolver<MatrixXd> es1(H1);   
  // VectorXd ev01(N),ev11(N);
  //   ev01 = es1.eigenvectors().col(0).normalized();  // ith eigenvector
  //   ev01 /= sqrt(dx);  
  //   ev11 = es1.eigenvectors().col(1).normalized();  // ith eigenvector
  //   ev11 /= sqrt(dx);      
  //   // cout<<ev<<endl;                       // normalize
  //   cout << "N = 1, L = 0, S = 1, J = 1, mass = "<<es1.eigenvalues()[0] +2.96<<"GeV" << endl;
  //   cout << "N = 2, L = 0, S = 1, J = 1, mass = "<<es1.eigenvalues()[1] +2.96 <<"GeV"<< endl;
  
  // MatrixXd H2 = En(N,1,0,dx,1);
  // SelfAdjointEigenSolver<MatrixXd> es1(H1);   
  // VectorXd ev01(N),ev11(N);
  //   ev01 = es1.eigenvectors().col(0).normalized();  // ith eigenvector
  //   ev01 /= sqrt(dx);  
  //   ev11 = es1.eigenvectors().col(1).normalized();  // ith eigenvector
  //   ev11 /= sqrt(dx);      
  //   // cout<<ev<<endl;                       // normalize
  //   cout << "N = 1, L = 0, S = 1, J = 1, mass = "<<es1.eigenvalues()[0] +2.96<<"GeV" << endl;
  //   cout << "N = 2, L = 0, S = 1, J = 1, mass = "<<es1.eigenvalues()[1] +2.96 <<"GeV"<< endl;
  

  
  
  
  
   
   


view.add(&prof);
        view.add(&prof2);
  view.show();
  window.show();
  app.exec();
  return 1;

}
