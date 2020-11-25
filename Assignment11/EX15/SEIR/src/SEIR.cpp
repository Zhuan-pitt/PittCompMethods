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
#include "QatPlotting/PlotFunction1D.h"

int main (int argc, char **argv) {


  using namespace Genfun;
  using namespace std;
     double b=0.0004;
     double d=0.004;
     double gam=0.1;
     double v=0.003;
     double a=0.1;
     double beta=0.2;
     double S0= 1-1E-6;
     double I0= 1E-6;
    Variable S(0,4),E(1,4),I(2,4),R(3,4);

 

    GENFUNCTION DSDt = b*(S+I+E+R)-(beta*I/(S+I+E+R)+d)*S+v*R;
    GENFUNCTION DEDt = beta*I/(S+I+E+R)*S-(d+a)*E;
    GENFUNCTION DIDt = a*E -(d+gam)*I;
    GENFUNCTION DRDt = gam*I-(v+d)*R;

    RKIntegrator integrator;
    integrator.addDiffEquation(&DSDt,"S",S0);
    integrator.addDiffEquation(&DEDt,"E",0);
    integrator.addDiffEquation(&DIDt,"I",I0);
    integrator.addDiffEquation(&DRDt,"R",0);
    
    

    GENFUNCTION s = *integrator.getFunction(S);
    GENFUNCTION e = *integrator.getFunction(E);
    GENFUNCTION i = *integrator.getFunction(I);
    GENFUNCTION r = *integrator.getFunction(R);
    
    


  
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax(1200);
  rect.setYmin(1E-7);
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
 

  
  // PlotOrbit px(x,y,0,13);
  PlotFunction1D pN = s+i+e+r;
  PlotFunction1D pi = i;
  
  view.add(&pi);
  // view.add(&pN);
  
  
  
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

