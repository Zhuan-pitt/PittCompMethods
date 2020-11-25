#include "QatGenericFunctions/RKIntegrator.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Square.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/FixedConstant.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotOrbit.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QAction>
#include "QatPlotting/PlotPoint.h"

int main (int argc, char **argv) {


  using namespace Genfun;
  using namespace std;
  double g = 1;
  double l1 = 1;
  double l2 = 1;
  double m1 = 1;
  double m2 = 1;
  double Theta10 = 3.1415926;
  double Theta20 = 3.1415926;
    Sin sin;
    Cos cos;



    Variable Theta1(0,4),Theta2(1,4),P1(2,4),P2(3,4);
    GENFUNCTION T = (m2*l2*l2*P1*P1 + (m1+m2)*l1*l1*P2*P2 - 2*m2*l1*l2*P1*P2*cos(Theta1-Theta2))
                            / (2*m2*l1*l1*l2*l2 * (m1 + m2*(sin(Theta1 - Theta2)*sin(Theta1 - Theta2))));
    GENFUNCTION V = -(m1+m2)*g*l1*cos(Theta1) - m2*g*l2*cos(Theta2);
    GENFUNCTION H = T + V;

    GENFUNCTION DTheta1Dt = H.partial(P1);
   GENFUNCTION DTheta2Dt = H.partial(P2);
    GENFUNCTION DP1Dt = -H.partial(Theta1);
    GENFUNCTION DP2Dt = -H.partial(Theta2);

    RKIntegrator integrator;
    integrator.addDiffEquation(&DTheta1Dt, "Theta1", Theta10);
    integrator.addDiffEquation(&DTheta2Dt, "Theta2", Theta20);
    integrator.addDiffEquation(&DP1Dt, "P1", 0);
    integrator.addDiffEquation(&DP2Dt, "P2", 0);
    GENFUNCTION theta1 = *integrator.getFunction(Theta1);
    GENFUNCTION theta2 = *integrator.getFunction(Theta2);

  cout<<theta1(10)<<endl;
  
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-100.2);
  rect.setXmax(100);
  rect.setYmin(-100);
  rect.setYmax(100);
 

 

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
 

  
  PlotOrbit px(theta1,theta2,0,1000);
  view.add(&px);
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "\u03B81"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "\u03B82"
	       << PlotStream::EndP();
  
  view.show();
  window.show();
  app.exec();



  return 1;

}

