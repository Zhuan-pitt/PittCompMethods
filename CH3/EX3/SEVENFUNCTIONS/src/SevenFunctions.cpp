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
//  In this example we are going to plot this function:

typedef double (*FnPtr)(double);
double f1(double x) {
  return sin(x);
}

double f2(double x) {
  return sin(5*x);
}

double f3(double x) {
  return sin(x*x);
}

double f4(double x) {
  return sin(x)*exp(-x);
}
double f5(double x) {
  return 15*x*(1-x*x);
}

double f6(double x) {
  return cos(x);
}
double f7(double x) {
  return -sin(x);
}
int main (int argc, char * * argv) {
  int index;
  std::cout<<"Choose the function you want to print"<<std::endl;
  std::cout<<"(1) f1(x)=sin(x)"<<std::endl;
  std::cout<<"(2) f2(x)=sin(5x)"<<std::endl;
  std::cout<<"(3) f3(x)=sin(x^2)"<<std::endl;
  std::cout<<"(4) f4(x)=e^(-x)sin(x)"<<std::endl;
  std::cout<<"(5) The associated Legendre polynomial, f5(x)=P^2_3(x)"<<std::endl;
  std::cout<<"(6) f6(x)=cos(x)"<<std::endl;
  std::cout<<"(7) f7(x)=cos(x)'=-sin(x)"<<std::endl;
  std::cin>>index;


  std::map <std::string,FnPtr> myMap;
  myMap["f1"]=f1;
  myMap["f2"]=f2;
  myMap["f3"]=f3;
  myMap["f4"]=f4;
  myMap["f5"]=f4;
  myMap["f6"]=f6;
  myMap["f7"]=f7;
 

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
  rect.setYmin(-1.2);
  rect.setYmax( 1.2);
  
  // Now create a "PlotView" and put it in the window.  This is a set of
  // axes onto which one can plot functions and draw other objects. 
  PlotView view(rect);
  window.setCentralWidget(&view);
  
  
  // Here we make plots out of our function, first by adapting to an F1D
  // and then by adapting to a PlotFunction1D:
 
  PlotFunction1D pF=Genfun::F1D(myMap["f"+std::to_string(index)]);
  {
    // Set plot properties here: thick, dark red
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pF.setProperties(prop);
  }
  
  // And we add them to the plotter:
  view.add(&pF);
  
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "f"+std::to_string(index)
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
