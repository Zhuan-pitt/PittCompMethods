#include "QatGenericFunctions/RKIntegrator.h"
#include <QatGenericFunctions/SimpleRKStepper.h>
#include <QatGenericFunctions/ButcherTableau.h>
#include <QatGenericFunctions/AdaptiveRKStepper.h>
#include <QatGenericFunctions/StepDoublingRKStepper.h>
#include "QatPlotting/PlotFunction1D.h"
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
#include "QatPlotting/PlotFunction1D.h"

int main (int argc, char **argv) {
struct PPoint
{
  double x;
  double y;
};
std::vector<PPoint> dev_e;
std::vector<PPoint> dev_m;
std::vector<PPoint> dev_te;
std::vector<PPoint> dev_c;
 
  using namespace Genfun;
  using namespace std;

  double x0 = 0;
  double eta0=1;
  double h =1;
  double re = exp(-5)*2/sqrt(3)*sin(sqrt(3)/2*10);

    Variable x(0,2),eta(1,2);

    GENFUNCTION Dx = eta;
    GENFUNCTION Deta = -eta-x;


for(double i = 1; i<7; i++){
  EulerTableau e;
    StepDoublingRKStepper stepper_E(e);
    AdaptiveRKStepper stepper_e(&stepper_E);
    stepper_e.tolerance() = h/pow(10,i);
    RKIntegrator integrator_e(&stepper_e);

    MidpointTableau mi;
     StepDoublingRKStepper stepper_M(mi);
    AdaptiveRKStepper stepper_m(&stepper_M);
    stepper_m.tolerance() = h/pow(10,i);
    RKIntegrator integrator_m(&stepper_m);
     
     TrapezoidTableau t;
     StepDoublingRKStepper stepper_T(t);
    AdaptiveRKStepper stepper_t(&stepper_T);
    stepper_t.tolerance() = h/pow(10,i);
    RKIntegrator integrator_t(&stepper_t);
    
    ClassicalRungeKuttaTableau c;
     StepDoublingRKStepper stepper_C(c);
    AdaptiveRKStepper stepper_c(&stepper_C);
    stepper_c.tolerance() = h/pow(10,i);
    RKIntegrator integrator_c(&stepper_c);
    


    integrator_c.addDiffEquation(&Dx,"x",x0);
    integrator_c.addDiffEquation(&Deta,"eta",eta0);
      integrator_e.addDiffEquation(&Dx,"x",x0);
    integrator_e.addDiffEquation(&Deta,"eta",eta0);
      integrator_m.addDiffEquation(&Dx,"x",x0);
    integrator_m.addDiffEquation(&Deta,"eta",eta0);
      integrator_t.addDiffEquation(&Dx,"x",x0);
    integrator_t.addDiffEquation(&Deta,"eta",eta0);
    

    GENFUNCTION X_c = *integrator_c.getFunction(x);
    dev_c.push_back({h/pow(10,i),abs(X_c(10)-re)});
      GENFUNCTION X_m = *integrator_m.getFunction(x);
    dev_m.push_back({h/pow(10,i),abs(X_m(10)-re)});
      GENFUNCTION X_t = *integrator_t.getFunction(x);
    dev_te.push_back({h/pow(10,i),abs(X_t(10)-re)});
    
      GENFUNCTION X_e = *integrator_e.getFunction(x);
    dev_e.push_back({h/pow(10,i),abs(X_e(10)-re)});

   }



  
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(1E-5);
  rect.setXmax(1);
  rect.setYmin(1E-16);
  rect.setYmax(1);
 

  PlotView view(rect);
  view.setLogX(true);
  view.setLogY(true);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);
     
   PlotProfile prof_t;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=4;
    prop.pen.setColor("blue");
    prop.brush.setStyle(Qt::SolidPattern);
    prof_t.setProperties(prop);
  }
     PlotProfile prof_e;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=4;
    prop.pen.setColor("red");
    prop.brush.setStyle(Qt::SolidPattern);
    prof_e.setProperties(prop);
  }
     PlotProfile prof_c;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=4;
    prop.pen.setColor("green");
    prop.brush.setStyle(Qt::SolidPattern);
    prof_c.setProperties(prop);
  }
     PlotProfile prof_m;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=4;
    prop.pen.setColor("orange");
    prop.brush.setStyle(Qt::SolidPattern);
    prof_m.setProperties(prop);
  }

  for(unsigned int i =0;i<dev_e.size();i++){
    prof_m.addPoint(dev_m[i].x,dev_m[i].y);
    prof_e.addPoint(dev_e[i].x,dev_e[i].y);
    prof_t.addPoint(dev_te[i].x,dev_te[i].y);
    prof_c.addPoint(dev_c[i].x,dev_c[i].y);
  }


 
  view.add(&prof_c);
   view.add(&prof_t);
   view.add(&prof_m);
   view.add(&prof_e);
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "h"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "deviation"
	       << PlotStream::EndP();
  
  view.show();
  window.show();
  app.exec();



  return 1;

}

