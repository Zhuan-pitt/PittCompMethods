#include "QatPlotWidgets/PlotView.h"

#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Abs.h"
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
#include <random>

int main (int argc, char **argv) {

  using namespace std;
  struct PPoint
{
  double x;
  double y;
};
  std::vector<PPoint> P;
  
  uniform_real_distribution<double> unth(0,3.14159);
  uniform_real_distribution<double> una(0,1);
  random_device dev;
  double N =1000000;

  for (double i =100;i<=1000;i=i+100){
      double M = 0;
  uniform_int_distribution<double> unx(0,i);
  for (int j =0;j<=N;j++){
  double x =unx(dev);
  double th = unth(dev);
  double a = una(dev);
  double p =exp(-x/(7.5*cos(th)));
  if (p>a){
    M=M+1;
  }

  }
  P.push_back({i,M/N});
  }
 
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(1.0);
  rect.setXmax(1000);
  rect.setYmin(0.5);
  rect.setYmax(1);
  
 

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
    prop.symbolSize=10;
    prop.pen.setColor("red");
    prof.setProperties(prop);
  }
  
 


  for(unsigned int i =0;i<= P.size();i++){
    prof.addPoint(P[i].x,P[i].y);
 

  }


   view.add(&prof);


  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "P"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Maximum of X"
	       << PlotStream::EndP();
  




  view.show();
  window.show();
  app.exec();
  return 1;

}

