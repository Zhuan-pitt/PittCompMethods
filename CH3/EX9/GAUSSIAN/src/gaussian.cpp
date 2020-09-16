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
#include <map>
#include <Eigen/Dense>
#include "QatPlotting/PlotPoint.h"

typedef std::complex<double> Complex;
using namespace Eigen;





int main (int argc, char **argv) {

  VectorXd R=VectorXd::Zero(7);
  //We break the region into 2^N intervals. 
  for (int N=1;N<=7;N++){
  
  MatrixXcd mat = MatrixXcd::Zero(pow(2,N+1)+2,pow(2,N+1)+2);
  
  double a = 1;
  double k = 1;
  double V0 = 0.8;
  double x=-4*a;
  Complex n = sqrt(Complex(1-V0*exp((-x*x)/(2*a*a))));//We set E=1;
  Complex I(0,1.0);
  
  mat(0,0)=exp(-I*k*(x));
  mat(0,1)=-exp(I*k*n*(x));
  mat(0,2)=-exp(-I*k*n*(x));
  
  
  mat(1,0)=-I*k*exp(-I*k*(x));
  mat(1,1)=-I*k*n*exp(I*k*n*(x));
  mat(1,2)=I*k*n*exp(-I*k*n*(x));
  
  

  for(int i = 2; i<=pow(2,N+1)-2;i=i+2){
    x=x+(8.*a)/pow(2.,N);
    Complex n1 = sqrt(Complex(1-V0*exp((-x*x)/(2*a*a))));
    
    mat(i,i-1)=exp(I*k*n*(x));
    mat(i,i)=exp(-I*k*n*(x));
    mat(i,i+1)=-exp(I*k*n1*(x));
    mat(i,i+2)=-exp(-I*k*n1*(x));;
  
    mat(i+1,i-1)=I*k*n*exp(I*k*n*(x));
    mat(i+1,i)=-I*k*n*exp(-I*k*n*(x));
    mat(i+1,i+1)=-I*k*n1*exp(I*k*n1*(x));
    mat(i+1,i+2)=I*k*n1*exp(-I*k*n1*(x));

    n=n1;
    
  }
  x=x+(8.*a)/pow(2.,N);
  

  mat(pow(2,N+1),pow(2,N+1)-1)=exp(I*k*n*(x));
  mat(pow(2,N+1),pow(2,N+1))=exp(-I*k*n*(x));
  mat(pow(2,N+1),pow(2,N+1)+1)=-exp(I*k*(x));
  
  mat(pow(2,N+1)+1,pow(2,N+1)-1)=I*k*n*exp(I*k*n*(x));
  mat(pow(2,N+1)+1,pow(2,N+1))=-I*k*n*exp(-I*k*n*(x));
  mat(pow(2,N+1)+1,pow(2,N+1)+1)=-I*k*exp(I*k*(x));

  VectorXcd vec = VectorXcd::Zero(pow(2,N+1)+2);
  vec(0)=-exp(I*k*(-4.*a));
  vec(1)=-I*k*exp(I*k*(-4.*a));
  

  VectorXcd coeff = mat.inverse()*vec;

  

  R(N-1)=norm(coeff(0));
  // std::cout<<R<<"\n"<<std::endl;
  
  }
  
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
  rect.setXmax(10);
  rect.setYmin(0);
  rect.setYmax(1);
  
  // Now create a "PlotView" and put it in the window.  This is a set of
  // axes onto which one can plot functions and draw other objects. 
  PlotView view(rect);
  window.setCentralWidget(&view);
 

 PlotPoint pR1(1,R(0));
 view.add(&pR1);
  PlotPoint pR2(2,R(1));
 view.add(&pR2); 
 PlotPoint pR3(3,R(2));
 view.add(&pR3);
  PlotPoint pR4(4,R(3));
 view.add(&pR4);
  PlotPoint pR5(5,R(4));
 view.add(&pR5);
  PlotPoint pR6(6,R(5));
 view.add(&pR6);
  PlotPoint pR7(7,R(6));
 view.add(&pR7);
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "probability density"
	      << PlotStream::EndP();
  
  // Label the x-axis
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "x"
	       << PlotStream::EndP();

  // Label the y-axis.
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "|\u03A6(x)|^2"
	       << PlotStream::EndP();
  
  // Show the window and start user interaction:
  window.show();
  app.exec();





  return 1;

}

