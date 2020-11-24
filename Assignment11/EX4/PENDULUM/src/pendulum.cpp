#include "QatGenericFunctions/RKIntegrator.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Tanh.h"
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
  double a = 1;
  double m = 1;
  double Theta0 = 0.3;
    Variable Theta(0,4),Phi(1,4),P_theta(2,4),P_phi(3,4);
    Sin sin;
    Cos cos;
    GENFUNCTION H = 1/(2*m*a*a)*(P_theta*P_theta + (P_phi*P_phi) / (sin(Theta)*sin(Theta))) - m*g*a * cos(Theta);

    GENFUNCTION DThetaDt = H.partial(P_theta);
    GENFUNCTION DPhiDt = H.partial(P_phi);
    GENFUNCTION DP_thetaDt = -H.partial(Theta);
    GENFUNCTION DP_phiDt = -H.partial(Phi);

    RKIntegrator integrator;
    integrator.addDiffEquation(&DThetaDt, "Theta", Theta0);
    integrator.addDiffEquation(&DPhiDt, "Phi", 0);
    integrator.addDiffEquation(&DP_thetaDt, "P_theta", 0);
    integrator.addDiffEquation(&DP_phiDt, "P_phi", 1);

    GENFUNCTION theta = *integrator.getFunction(Theta);
    GENFUNCTION phi = *integrator.getFunction(Phi);
    




  GENFUNCTION x = sin(theta)*cos(phi);
  GENFUNCTION y = sin(theta)*sin(phi);
  
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-1.2);
  rect.setXmax(1.2);
  rect.setYmin(-1.2);
  rect.setYmax(1.2);
 

 

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
 

  
  PlotOrbit px(x,y,0,13);
  view.add(&px);
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "x"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "y"
	       << PlotStream::EndP();
  
  view.show();
  window.show();
  app.exec();



  return 1;

}

