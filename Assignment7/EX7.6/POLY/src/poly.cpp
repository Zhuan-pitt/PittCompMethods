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
#include "QatGenericFunctions/Erf.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/LegendrePolynomial.h"

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
  rect.setXmin(-1);
  rect.setXmax( 1.0);
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
  Erf erf;
  // GENFUNCTION rho=1.5*exp(-X*X/8+2*(X/4-3)*(X/4-3))*(1+erf(0.3535*X-4.2426))
  // +1./(2*sqrt(2*3.14159))*exp(-X*X/8.);
  GENFUNCTION P1 = LegendrePolynomial(1);
  GENFUNCTION P3 = LegendrePolynomial(3);
  GENFUNCTION P5 = LegendrePolynomial(5);
  GENFUNCTION P7 = LegendrePolynomial(7);
  GENFUNCTION rho = (sqrt(3./8.)*P1-sqrt(7./6.)*P3+sqrt(11./24.)*P5-sqrt(15./16.)*P7)*
                     (sqrt(3./8.)*P1-sqrt(7./6.)*P3+sqrt(11./24.)*P5-sqrt(15./16.)*P7);
  PlotFunction1D prho = rho;
  // cout<<rho(0.5)<<endl;

  



   random_device dev;
   random_device dev2;
  uniform_real_distribution<double> un(-1,1);

  uniform_real_distribution<double> uny(0,1.1);
  //Here we set k_bT=1,m=2
  int nbin=100;
  int num = 30000;
  Hist1D his(nbin,-1,1);
  int N =0;
  for (int i=0;i<=10*num;i++){
    double x = un(dev);
    double y = uny(dev2);
    if (N<num){
    if (y<rho(x)){
    his.accumulate(x,1./(num*2)*nbin*0.8);
    N++;
    }
    }
  }

  
  PlotHist1D phis = his;





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
	      <<"Distribution Density"
	      << PlotStream::EndP();
  
  // Label the x-axis
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "cos(\u03B8)"
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





