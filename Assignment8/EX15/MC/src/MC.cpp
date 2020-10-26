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
  std::vector<PPoint> E1;
  std::vector<PPoint> E2;

  double ex = (exp(1)-2)/(exp(1)-1);
  

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(1.0);
  rect.setXmax(1000);
  rect.setYmin(1E-5);
  rect.setYmax(1);
  
 

  PlotView view(rect);
  view.setLogX(true);
  view.setLogY(true);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);




  
  using namespace Genfun;


  random_device dev;
  uniform_real_distribution<double> un(0,1);
  

  for (double j =0; j <=200;j=j+1){
      double inte1 = 0;
      double inte2 = 0;
  for (int k =0;k<=50;k++){
    double inte1_1 = 0;
    double inte2_1 = 0;
    for (int i=0;i<=(j+1)*5;i++){
    
      double x2 = un(dev);
      inte1_1 = (exp(x2)-1)/(exp(1)-1)+inte1_1;
      double y=sqrt(x2);
      inte2_1 = (exp(y)-1)/(2*y*(exp(1)-1))+inte2_1;
    
    }
    inte1=inte1+((inte1_1/((j+1)*5))-ex)*((inte1_1/((j+1)*5))-ex);
    inte2=inte2+((inte2_1/((j+1)*5))-ex)*((inte2_1/((j+1)*5))-ex);
  }
  E1.push_back({(j+1)*5,sqrt(inte1/50.)});
  E2.push_back({(j+1)*5,sqrt(inte2/50.)});
  }
      PlotProfile prof1;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=10;
    prop.pen.setColor("blue");
    // prop.brush.setStyle(Qt::SolidPattern);
    prof1.setProperties(prop);
  }
      PlotProfile prof;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=10;
    prop.pen.setColor("red");
    // prop.brush.setStyle(Qt::SolidPattern);
    prof.setProperties(prop);
  }
  
 


  for(unsigned int i =0;i<= E1.size();i++){
    prof.addPoint(E1[i].x,E1[i].y);
    prof1.addPoint(E2[i].x,E2[i].y);

  }


   view.add(&prof);
  view.add(&prof1);


  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Error of two MC integral"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "N"
	       << PlotStream::EndP();
  




  view.show();
  window.show();
  app.exec();
  return 1;

}



