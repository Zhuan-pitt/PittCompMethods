#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"

#include <random>
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatGenericFunctions/ASin.h"
#include "QatGenericFunctions/Sin.h"
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
#include <cmath>
#include "QatPlotting/PlotPoint.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"



int main (int argc, char **argv) {
      struct PPoint
{
  double x;
  double y;
};



std::vector<PPoint> disp={{400,1.339},{450,1.337},{500,1.335},{550,1.333},{600,1.332},
{650,1.331},{700,1.331},{750,1.331}};


  using namespace std;
  using namespace Genfun;
  random_device dev;
  random_device dev2;
  uniform_real_distribution<double> un(0,1);
  exponential_distribution<double> ex(3);
  //Here we set k_bT=1,m=2
  int nbin=100;
  int num = 100000;
  double range = 0.8;
  Hist1D his(nbin,0,range);
  Hist1D his2(nbin,0,range);
  Hist1D his3(nbin,0,range);
  Hist1D his4(nbin,0,range);
  for (int i=0;i<=num;i++){
    double x = asin(un(dev));
    his.accumulate(4*asin(sin(x)/disp[0].y)-2*x,1./(num*range)*nbin);
   his2.accumulate(4*asin(sin(x)/disp[2].y)-2*x,1./(num*range)*nbin);
   his3.accumulate(4*asin(sin(x)/disp[4].y)-2*x,1./(num*range)*nbin);
   his4.accumulate(4*asin(sin(x)/disp[7].y)-2*x,1./(num*range)*nbin);
  
  }

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax(0.8);
  rect.setYmin(0);
  rect.setYmax(10);
  
 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);




 PlotHist1D phis = his;
  PlotHist1D phis2 = his2;
   PlotHist1D phis3 = his3;
    PlotHist1D phis4 = his4;
   PlotProfile prof1;
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("red");
    phis4.setProperties(prop);
  }
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("orange");
    phis3.setProperties(prop);
  }
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("green");
    phis2.setProperties(prop);
  }
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("blue");
    phis.setProperties(prop);
  }
 view.add(&phis);
view.add(&phis2);
 view.add(&phis3);
 view.add(&phis4);
 
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Probability Density Distribution"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "\u03C6"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << ""
	       << PlotStream::EndP();
  
  view.show();
  window.show();
  app.exec();
  return 1;

}

