#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/SimpleIntegrator.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/Sinh.h"
#include "QatGenericFunctions/Cosh.h"
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

  using namespace Genfun;
  
  Variable X;
  Sqrt sqrt;
  Cosh cosh;
  Sinh sinh;
  GENFUNCTION f = Tanh();

  GENFUNCTION f2 = sqrt(cosh(X)/sinh(X));
  
  TrapezoidRule rule2;
  MidpointRule rule1;
  SimpsonsRule rule3;

  struct PPoint
{
  double x;
  double y;
};

std::vector<PPoint> error1={{0,0},{0,0},{0,0},{0,0}};
std::vector<PPoint> error2={{0,0},{0,0},{0,0},{0,0}};
std::vector<PPoint> error3={{0,0},{0,0},{0,0},{0,0}};
std::vector<PPoint> error4={{0,0},{0,0},{0,0},{0,0}};

for(unsigned int i = 2; i<=8;i=i+2){
  SimpleIntegrator inte1(0,1,rule1,i);
  SimpleIntegrator inte2(0,1,rule2,i);
  SimpleIntegrator inte3(0,1,rule3,i);
  error1[i/2-1].x=1./i;
  error1[i/2-1].y=abs((inte1(f)-log(cosh(1))));
  
  error2[i/2-1].x=1./i;
  error2[i/2-1].y=abs(inte2(f)-log(cosh(1)));
  
  error3[i/2-1].x=1./i;
  error3[i/2-1].y=abs(inte3(f)-log(cosh(1)));
  

  error4[i/2-1].x=1./i;
  error4[i/2-1].y=abs((inte1(f2)-2.061790486458692));

 }

 QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(0.5);
   rect.setYmin(1E-13);
  rect.setYmax(1);
 

 

  PlotView view(rect);
  view.setXZero(false);
  view.setLogY(true);
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
    PlotProfile prof2;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=10;
    prop.pen.setColor("orange");
    // prop.brush.setStyle(Qt::SolidPattern);
    prof2.setProperties(prop);
  }

  PlotProfile prof3;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=10;
    prop.pen.setColor("red");
    // prop.brush.setStyle(Qt::SolidPattern);
    prof3.setProperties(prop);
  }

 PlotProfile prof4;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=10;
    prop.pen.setColor("blue");
    prop.brush.setStyle(Qt::SolidPattern);
    prof4.setProperties(prop);
  }

  for(unsigned int i =0;i<error1.size();i++){
    prof1.addPoint(error1[i].x,error1[i].y);
    prof2.addPoint(error2[i].x,error2[i].y);
    prof3.addPoint(error3[i].x,error3[i].y);
    prof4.addPoint(error4[i].x,error4[i].y);

  }


  view.add(&prof1);
  view.add(&prof2);
  view.add(&prof3);
  // view.add(&prof4);
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Length of interval"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Error"
	       << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();
  return 1;

}

