#include "QatGenericFunctions/SimpleIntegrator.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/FixedConstant.h"
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
#include "QatGenericFunctions/Abs.h"
#include "QatGenericFunctions/GaussQuadratureRule.h"

#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include "QatGenericFunctions/RootFinder.h"






int main (int argc, char **argv) {

  struct PPoint
{
  double x;
  double y;
};
  using namespace Genfun;
  Variable X;
  Exp exp;
  Sqrt sqrt;
  Abs abs;
  std::vector<PPoint> Action;
  std::vector<PPoint> Action1;
  
  for(double E=600;E<=1800;E=E+50){
  //l=0
  GENFUNCTION J0=sqrt(abs(0.00356*(E+1./X-X*1000./1.16)));
  double rmax=(E+sqrt(E*E+4000/1.16))/2000.*1.16;

  //l=1 
  GENFUNCTION f = E+1./X-X*1000./1.16-28./(X*X);

  NewtonRaphson root(f,1.0E-12,100);
  double rmin1 = root.root(0.1);
  double rmax1 = root.root(0.8);

  GENFUNCTION J1=sqrt(abs(0.00356*(E+1./X-X*1000./1.16-28./(X*X))));
 

 
  MidpointRule rule;
  SimpleIntegrator inte(0,rmax,rule,3000);

  Action.push_back({E,inte(J0)});
  SimpleIntegrator inte1(rmin1,rmax1,rule,3000);

  Action1.push_back({E,inte1(J1)});
  }
  

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(600);
  rect.setXmax(1800);
  rect.setYmin(0);
  rect.setYmax(3);
 

 

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
      PlotProfile prof;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=10;
    prop.pen.setColor("red");
    // prop.brush.setStyle(Qt::SolidPattern);
    prof.setProperties(prop);
  }
  
  Genfun::InterpolatingPolynomial P;
  Genfun::InterpolatingPolynomial P1;



  for(unsigned int i =0;i<Action.size();i++){
    prof.addPoint(Action[i].x,Action[i].y);
    P.addPoint(Action[i].x,Action[i].y);
    prof1.addPoint(Action1[i].x,Action1[i].y);
    P1.addPoint(Action1[i].x,Action1[i].y);


    
  }


  view.add(&prof);
  view.add(&prof1);
  PlotFunction1D pP=P;
  PlotFunction1D pP1=P1;
  view.add(&pP);
  view.add(&pP1);

  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Energy [MeV]"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Action"
	       << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();






  return 1;

}

