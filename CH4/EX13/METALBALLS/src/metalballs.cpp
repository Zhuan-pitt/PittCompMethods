#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/F1D.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include "Eigen/Dense"
#include <Eigen/Eigenvalues> 
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Cos.h"
#include <map>

int main (int argc, char * * argv) {

  using namespace Eigen;

  MatrixXd A = MatrixXd::Zero(5,5);

  A(0,0) = -1; A(0,1)=1;
  A(1,0) = 1; A(1,1)=-3;A(1,2)=2;
  A(2,1) = 2; A(2,2)=-4;A(2,3)=2;
  A(3,2) =2; A(3,3)=-3;A(3,4)=1;
  A(4,3)=1; A(4,4)=-1;
  // solve the mormal mode
  SelfAdjointEigenSolver<MatrixXd> es(A);
  // std::cout<<es.eigenvectors().col(4)<<std::endl;
  MatrixXd Eig=es.eigenvectors().inverse();
 //At t=0, the velocity of each metal ball is 0, therefore
 // X=d*cos(wt) for each normal mode

 VectorXd B = VectorXd::Zero(5);
 //Boundary conditions
 B(0)=-2;B(1)=9;B(2)=0;B(3)=-3;B(4)=4;

 //Coefficients
 VectorXd D = VectorXd::Zero(5);
 VectorXd w = VectorXd::Zero(5);
 for(int i=0; i<=4;i++){
   D(i)=B.transpose().dot(es.eigenvectors().col(i));
   w(i)=sqrt(abs(es.eigenvalues()[i]));
 }
// X_i=D(i)cos(w(i)*T)
  // This is example code demonstrating how to visualize functions
  // using the QAT libraries.

  // It plots f(x) where f(x) is a function defined just above:


  // This part is "boilerplate" from the Qt package.  It sets up a window
  // which is part of the graphical user interface.  It adds a toolbar
  // with a "Quit" button, and the button has a keyboard accerator: the
  // q key can be pressed to quit the application. Interested users
  // can consult the Qt documentation for more information. 
  
  QApplication     app(argc,argv);
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  quitAction->setShortcut(QKeySequence("q"));
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));

  // The following code sets the scale for a linear plot:
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax( 15.0);
  rect.setYmin(-8);
  rect.setYmax( 10);
  
  // Now create a "PlotView" and put it in the window.  This is a set of
  // axes onto which one can plot functions and draw other objects. 
  PlotView view(rect);
  window.setCentralWidget(&view);
  using namespace Genfun;
Variable T;
Cos cos;

GENFUNCTION X0=D(0)*cos(w(0)*T);
GENFUNCTION X1=D(1)*cos(w(1)*T);
GENFUNCTION X2=D(2)*cos(w(2)*T);
GENFUNCTION X3=D(3)*cos(w(3)*T);
GENFUNCTION X4=D(4)*cos(w(4)*T);

GENFUNCTION x0 = Eig(0,0)*X0+Eig(1,0)*X1+Eig(2,0)*X2+Eig(3,0)*X3+Eig(4,0)*X4;
GENFUNCTION x1 = (Eig(0,1)*X0+Eig(1,1)*X1+Eig(2,1)*X2+Eig(3,1)*X3+Eig(4,1)*X4)/3.;
GENFUNCTION x2 = (Eig(0,2)*X0+Eig(1,2)*X1+Eig(2,2)*X2+Eig(3,2)*X3+Eig(4,2)*X4)/2.;
GENFUNCTION x3 = Eig(0,3)*X0+Eig(1,3)*X1+Eig(2,3)*X2+Eig(3,3)*X3+Eig(4,3)*X4;
GENFUNCTION x4 = (Eig(0,4)*X0+Eig(1,4)*X1+Eig(2,4)*X2+Eig(3,4)*X3+Eig(4,4)*X4)/2.;

 PlotFunction1D px0=x0;
 PlotFunction1D px1=x1;
 PlotFunction1D px2=x2;
 PlotFunction1D px3=x3; 
 PlotFunction1D px4=x4;
 PlotFunction1D pxc=(x0+3*x1+2*x2+x3+2*x4)/9.;

std::cout<<"Choose the position you want to plot"<<"\n"
<<"0. x_0(T)\n"
<<"1. x_1(T)\n"
<<"2. x_2(T)\n"
<<"3. x_3(T)\n"
<<"4. x_4(T)\n"
<<"5. x_c(T), center of mass.\n"<<std::endl;

int index;
std::cin>>index;
  
if (index==0){
  view.add(&px0);
}
if (index==1){
  view.add(&px1);
}
if (index==2){
  view.add(&px2);
}
if (index==3){
  view.add(&px3);
}
if (index==4){
  view.add(&px4);
}
if (index==5){
  view.add(&pxc);
}
  // view.add(&px1);
  // view.add(&px2);
  // view.add(&px3);
  // view.add(&px4);
  
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << ""
	      << PlotStream::EndP();
  
  // Label the x-axis
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "T"
	       << PlotStream::EndP();

  // Label the y-axis.
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Position"
	       << PlotStream::EndP();
  
  // Show the window and start user interaction:
  window.show();
  app.exec();



  // -------------------------------------------------:
  return 1;

}

