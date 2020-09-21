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
#include "QatPlotting/PlotPoint.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"


int main (int argc, char **argv) {
  struct PPoint
{
  double x;
  double y;
};
//The coordinates of bus stations read from the diagram
  
std::vector<PPoint> price={{2007,346},{2008,654},{2009,724},{2010,873},{2011,1410}};
  



  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(2006.0);
  rect.setXmax(2015);
  rect.setYmin(100.0);
  rect.setYmax(16000);
  
 

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
  Genfun::InterpolatingPolynomial P;
  Genfun::CubicSplinePolynomial Pc;
  for(unsigned int i =0;i<price.size();i++){
    prof.addPoint(price[i].x,price[i].y);
    P.addPoint(price[i].x,price[i].y);
    Pc.addPoint(price[i].x,price[i].y);
  }
  PlotFunction1D pP = P;
  PlotFunction1D pPc = Pc;

  {
    // Set plot properties here: thick solid line for Sine
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    prop.pen.setColor("red");
    pP.setProperties(prop);
  }
  {
    // Set plot properties here: thick solid line for Sine
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    prop.pen.setColor("orange");
    pPc.setProperties(prop);
  }

  view.add(&pP);

  view.add(&pPc);
  view.add(&prof);
  

  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Price trend of Chateau Lafitte Rothschild"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Year"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Price"
	       << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();
  return 1;

}

