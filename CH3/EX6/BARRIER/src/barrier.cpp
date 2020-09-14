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
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
typedef std::complex<double> Complex;



double f(double x) {
  return sin((x));
}

int main (int argc, char **argv) {

  //Set bar{h}/2m==1
  double v = 0.5; //v=V/E
  double n = sqrt(1.0-v); //index of refraction
  double k = 1.0;// k =sqrt(E)
  
  Complex I(0,1.0);
  Complex nk=k*sqrt(Complex(1-v));

  Eigen::VectorXcd Y(4); 
  Y(0)= -exp(-I*k); 
  Y(1)= 0; 
  Y(2)= -I*k*exp(-I*k); 
  Y(3)= 0;

  Eigen::MatrixXcd A(4,4); // First row:

  A(0,0)= exp(I*k) ; 
  A(0,1)=-exp(-I*nk) ; 
  A(0,2)= -exp(I*nk) ; 
  A(0,3)=0 ;

  // Second row: 
  A(1,0)= 0;
  A(1,1)= exp(I*nk);
  A(1,2)= exp(-I*nk);
  A(1,3)=-exp(I*k);

  // Third row:
  A(2,0)= -I*k*exp(I*k) ; 
  A(2,1)=-I*nk*exp(-I*nk); 
  A(2,2)= I*nk*exp(I*nk) ; 
  A(2,3)=0 ;

  // Fourth row: 
  A(3,0)= 0;
  A(3,1)=I*nk*exp(I*nk);
  A(3,2)=-I*nk*exp(-I*nk); 
  A(3,3)=-I*k*exp(I*k) ;

  Eigen::VectorXcd BCDF=A.inverse()*Y;
  Complex B=BCDF(0);
  Complex C=BCDF(1);
  Complex D=BCDF(2);
  Complex F=BCDF(3);
  

  std::cout<<BCDF<<std::endl;






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
  rect.setXmin(-2.0);
  rect.setXmax( 2.0);
  rect.setYmin(-3);
  rect.setYmax( 3);
  
  // Now create a "PlotView" and put it in the window.  This is a set of
  // axes onto which one can plot functions and draw other objects. 
  PlotView view(rect);
  window.setCentralWidget(&view);
  using namespace Genfun;
  Variable X;
  Cos cos;
  Sin sin;
  GENFUNCTION FL = 1+2*B.real()*cos(2*k*X)+2*B.imag()*sin(2*k*X)+norm(B);
  GENFUNCTION FM = norm(C)+2*(C.real()*D.real()+C.imag()*D.imag())
                    *cos(2*n*k*X)+2*(C.real()*D.imag()-C.imag()*D.real())
                    *sin(2*n*k*X)+norm(D);
  GENFUNCTION FR = norm(F)+X-X;

  // Here we make plots out of our function, first by adapting to an F1D
  // and then by adapting to a PlotFunction1D:
 
 PlotFunction1D pFL =FL;
 PlotFunction1D pFM =FM;
 PlotFunction1D pFR =FR;
  {
    // Set plot properties here: thick, dark red
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pFL.setProperties(prop);
  }
  
  // And we add them to the plotter:
  view.add(&pFL);
  view.add(&pFM);
  view.add(&pFR);
  
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "f"
	      << PlotStream::Normal()
	      <<"(x)"
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
	       << "f(x)"
	       << PlotStream::EndP();
  
  // Show the window and start user interaction:
  window.show();
  app.exec();


  return 1;

}

