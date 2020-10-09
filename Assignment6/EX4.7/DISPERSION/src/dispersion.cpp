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
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <libgen.h>
#include <cmath>
#include "QatPlotting/PlotPoint.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"



int main (int argc, char **argv) {
      struct PPoint
{
  double x;
  double y;
};



std::vector<PPoint> disp={{200,1.396},{250,1.362},{300,1.349},{350,1.343},{400,1.339},{450,1.337},{500,1.335},{550,1.333},{600,1.332},
{650,1.331},{700,1.331},{750,1.331},{750,1.33},{800,1.329},{850,1.329},{900,1.328},{950,1.327},{1000,1.327}};

std::vector<PPoint> displog=disp;
for(unsigned int i =0; i< disp.size();i++){
  displog[i].y=log(disp[i].y-1);
}


  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(100);
  rect.setXmax(1100);
  rect.setYmin(1);
  rect.setYmax(2);
  
 

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
    prop.pen.setColor("blue");
    prop.brush.setStyle(Qt::SolidPattern);
    prof.setProperties(prop);
  }


  
  using namespace Genfun; 
  Exp exp;
  // Genfun::InterpolatingPolynomial P;
  Genfun::CubicSplinePolynomial Pc;
  for(unsigned int i =0;i<disp.size();i++){
    prof.addPoint(disp[i].x,disp[i].y);
    // P.addPoint(disp[i].x,displog[i].y);
    if (i<=10){
    Pc.addPoint(disp[i].x,displog[i].y);
    }
  }
  // PlotFunction1D pP = exp(P)+1;
  PlotFunction1D pPc = exp(Pc)+1;


 
  {
    // Set plot properties here: thick solid line for Sine
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    prop.pen.setColor("orange");
    pPc.setProperties(prop);
  }

  // view.add(&pP);

  view.add(&pPc);
  view.add(&prof);
  

  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Index of refraction of water vs. wavelength"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Wavelength (nm)"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Index of refraction"
	       << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();
  return 1;

}

