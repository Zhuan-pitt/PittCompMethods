#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Abs.h"
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
#include <random>


int main (int argc, char **argv) {
using namespace std;
struct PPoint
{
  double x;
  double y;
};
  std::vector<PPoint> Ns;
  std::vector<PPoint> Na;
  

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(1.0);
  rect.setXmax(10);
  rect.setYmin(0.0);
  rect.setYmax(2);
  
 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);




  
  using namespace Genfun;
  Exp exp;
  Sqrt sqrt;
  Abs abs;
  Variable X(0,4),Y(1,4),Z(2,4),D(3,4); 
  // Variable d;
  // GENFUNCTION g = x;
  
  GENFUNCTION psi_1 = 1./1.7724*exp(-sqrt(abs(X*X+Y*Y+(Z-D/2.)*(Z-D/2.))));
  GENFUNCTION psi_2 = 1./1.7724*exp(-sqrt(abs(X*X+Y*Y+(Z+D/2.)*(Z+D/2.))));

  GENFUNCTION f1 = (psi_1+psi_2)*(psi_1+psi_2)*exp(X+Y+Z);
  GENFUNCTION f2 = (psi_1-psi_2)*(psi_1-psi_2)*exp(X+Y+Z);
  GENFUNCTION f3 = psi_1*psi_1*exp(X+Y+Z);
  random_device dev;
  exponential_distribution<double> ex(1);
  int N=500000;

  
  for (double d =1; d<=10; d= d+0.5){
    double inte1=0;
    double inte2=0;
    for (int i =0; i<=N;i++){
    
    
      double x = ex(dev);
      double y = ex(dev);
      double z = ex(dev);
      inte1 =inte1 + f1({x,y,z,d});
      // inte1 = inte1+ f3({x,y,z,0});
      inte2 =inte2 + f2({x,y,z,d});
      
    }
    // cout<<inte1<<endl;
    // Ns.push_back({d,sqrt(N/(8*inte1))});
    // Na.push_back({d,sqrt(N/(8*inte2))});
     Ns.push_back({d,((8*inte1)/N)});
    Na.push_back({d,((8*inte2)/N)});
  }
  // cout<<Ns[0].x<<endl;
  // cout<<Na[0].x<<endl;
  // cout<<Ns[0].y<<endl;
  // cout<<Na[0].y<<endl;

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
  
 


  for(unsigned int i =0;i<= Ns.size();i++){
    prof.addPoint(Ns[i].x,Ns[i].y);
    prof1.addPoint(Na[i].x,Na[i].y);

  }


  view.add(&prof);
  view.add(&prof1);


  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Energy"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Distance"
	       << PlotStream::EndP();
  
  // PlotStream yLabelStream(view.yLabelTextEdit());
  // yLabelStream << PlotStream::Clear()
	//        << PlotStream::Center()
	//        << PlotStream::Family("Sans Serif")
	//        << PlotStream::Size(16)
	//        << "Price"
	//        << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();
  return 1;

}

