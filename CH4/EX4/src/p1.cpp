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
#include <cmath>
#include <libgen.h>
#include "QatPlotting/PlotPoint.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"
#include "QatPlotting/PlotOrbit.h"


int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }
  
struct PPoint
{
  double x;
  double y;
  double t;
};
//The coordinates of bus stations read from the diagram
// t = arctan(y/x)
std::vector<PPoint> station={{-232,144,0},{-132,222,0},{-5,208,0},
                              {31,219,0},{119,187,0},{154,158,0},
                              {165,113,0},{162,34,0},{193,2,0}};

for(unsigned int i =0;i<station.size();i++){
  station[i].t=atan2(station[i].x,station[i].y);

}
// std::cout<<station[1].t<<std::endl;

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-360.0);
  rect.setXmax(271);
  rect.setYmin(-80.0);
  rect.setYmax(362);
  
 

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
  Genfun::CubicSplinePolynomial X;
  Genfun::CubicSplinePolynomial Y;

  for(unsigned int i =0;i<station.size();i++){
    prof.addPoint(station[i].x,station[i].y);
    X.addPoint(station[i].t,station[i].x);
    Y.addPoint(station[i].t,station[i].y);
    
  }
  // PlotFunction1D proute = route;
  PlotOrbit proute (X, Y, -1.015,1.57);


  {
    // Set plot properties here: thick solid line for Sine
    PlotOrbit::Properties prop;
    prop.pen.setWidth(3);
    prop.pen.setColor("red");
    proute.setProperties(prop);
  }

  view.add(&proute);
  view.add(&prof);
  


  char *wd=dirname(argv[0]);
  std::string imageName=std::string(wd)+"/../../src/p1.png";
  QPixmap imagePix(imageName.c_str());
  QGraphicsPixmapItem imagePixItem;
  imagePixItem.setPixmap(imagePix);
  //imagePixItem.setFlags(QGraphicsItem::ItemIsMovable);
  view.scene()->addItem(&imagePixItem);
  imagePixItem.setScale(1.0);
  imagePixItem.setPos(130,130);


  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "P1 Bus interpolated position"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "X position, pixel units"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Y position, pixel units"
	       << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();
  return 1;
}

