#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/GaussIntegrator.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Tanh.h"
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



int main (int argc, char **argv) {
  using namespace Genfun;
  Variable X;
  Exp exp;
  Sqrt sqrt;
  Abs abs;
  double V0=1;
  double a=1;
  double m;
  double e ;

    struct PPoint
{
  double x;
  double y;
};



std::vector<PPoint> num={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
{0,0},{0,0},{0,0},{0,0},{0,0}};




  for(unsigned int i=0;i<=14;i++){
  e = 0;
  m=i/10.;
  GENFUNCTION v=-V0*exp(-X*X/(2.*a*a));
  GENFUNCTION f = 2*sqrt(abs(2*m*(e-v)));

  //Solve the two zero points
  double x0; double x1;
  x0 = -sqrt(2*a*a*log(-V0/e));
  x1 = sqrt(2*a*a*log(-V0/e));

  GaussHermiteRule rule3(argc==2 ? std::stoi(argv[1]):20);
  GaussIntegrator inte3(rule3);
  // std::cout<<inte3(f)<<std::endl;
  num[i].x=m;
  num[i].y=inte3(f);

  }
  GENFUNCTION n = 4*a*sqrt(2*X*3.14159265359);


  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax(1.5);
  rect.setYmin(-1.2);
  rect.setYmax(12);
 

 

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
  for(unsigned int i =0;i<num.size();i++){
    prof1.addPoint(num[i].x,num[i].y);
    
  }


  view.add(&prof1);
 
  PlotFunction1D pn=n;
  view.add(&pn);

  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Mass"
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

