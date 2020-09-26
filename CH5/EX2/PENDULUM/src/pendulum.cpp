#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/SimpleIntegrator.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/Sinh.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Tanh.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Variable.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
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
#include "QatPlotting/PlotPoint.h"

int main (int argc, char **argv) {

  // T0=sqrt(l/g)
  // we set T0 = 1

  using namespace Genfun;
  Variable X;
  Sqrt sqrt;
  Cos cos;
  struct PPoint
{
  double x;
  double y;
};

std::vector<PPoint> period={{1./12,0},{1./6,0},{1./3,0},{1./2,0},{2./3,0},{5./6,0},{11./12}};

  for(unsigned int i =0;i<period.size();i++){
  GENFUNCTION f = 1/sqrt(cos(X)-cos(atan(1)*4*period[i].x));
  MidpointRule rule3;
  SimpleIntegrator inte3(-atan(1)*4*period[i].x,atan(1)*4*period[i].x,rule3,30000);
  period[i].y=inte3(f);
  period[i].x=atan(1)*4*period[i].x;
  

  }

QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(3.1415);
  rect.setYmin(0);
  rect.setYmax(15);
 

 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);

  PlotProfile prof1;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=10;
    prop.pen.setColor("blue");
    // prop.brush.setStyle(Qt::SolidPattern);
    prof1.setProperties(prop);
  }
 


  for(unsigned int i =0;i<period.size();i++){
    prof1.addPoint(period[i].x,period[i].y);
    
  }


  view.add(&prof1);
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Maximum amplitudes"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Period"
	       << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();



  return 1;

}

