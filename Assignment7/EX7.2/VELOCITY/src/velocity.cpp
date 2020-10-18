#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/F1D.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Variable.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
int main (int argc, char **argv) {
  using namespace std;
  using namespace Genfun;
  random_device dev;
  gamma_distribution<double> ga(2,1);
  //Here we set k_bT=1,m=2
  int nbin=500;
  int num = 100000;
  double range = 10;
  Hist1D his(nbin,0,range);
  
  for (int i=0;i<=num;i++){
    double x = ga(dev);
    his.accumulate(sqrt(x),1./(num*range)*nbin/(sqrt(x))*1.1238);
  }

  PlotHist1D phis = his;
  // Automatically generated:-------------------------:

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
  rect.setXmax( 4.0);
  rect.setYmin(0);
  rect.setYmax(1.2);
  
  // Now create a "PlotView" and put it in the window.  This is a set of
  // axes onto which one can plot functions and draw other objects. 
  PlotView view(rect);
  window.setCentralWidget(&view);
  
  
  // Here we make plots out of our function, first by adapting to an F1D
  // and then by adapting to a PlotFunction1D:
  
  Variable X;
  Exp exp;
  Sqrt sqrt;
  GENFUNCTION rho=2.2567*X*X*exp(-X*X);
  PlotFunction1D prho = rho;
  
  // And we add them to the plotter:
  view.add(&phis);
  view.add(&prho);
  
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << PlotStream::Normal()
	      <<"Velocity distribution"
	      << PlotStream::EndP();
  
  // Label the x-axis
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "v"
	       << PlotStream::EndP();

  // Label the y-axis.
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "\u03c1(x)"
	       << PlotStream::EndP();
  
  // Show the window and start user interaction:
  window.show();
  app.exec();
 
  return 1;
}

