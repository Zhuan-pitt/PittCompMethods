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

#include <random>
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



std::vector<PPoint> disp={{400,1.339},{450,1.337},{500,1.335},{550,1.333},{600,1.332},
{650,1.331},{700,1.331}};


std::vector<PPoint> Pvi;

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-0.5);
  rect.setXmax(0.5);
  rect.setYmin(0.5);
  rect.setYmax(1);
  
 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);


  
    PlotProfile prof5;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("violet");
    prof5.setProperties(prop);
  }
  PlotProfile prof4;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("blue");
    prof4.setProperties(prop);
  }
  PlotProfile prof3;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("green");
    prof3.setProperties(prop);
  }
  PlotProfile prof2;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("yellow");
    prof2.setProperties(prop);
  }
    PlotProfile prof1;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("red");
    prof1.setProperties(prop);
  }


  using namespace std;
  random_device dev;
  uniform_real_distribution<double> un(0.67,0.685);
  uniform_real_distribution<double> vi(400,450);
  uniform_real_distribution<double> re(620,700);
  uniform_real_distribution<double> ye(580,620);
  uniform_real_distribution<double> gr(550,580);
  uniform_real_distribution<double> bl(450,550);
  
  uniform_real_distribution<double> the(-0.7,0.7);
 
  
  using namespace Genfun; 
  
  // Genfun::InterpolatingPolynomial P;
  Genfun::CubicSplinePolynomial Pc;
  for(unsigned int i =0;i<disp.size();i++){
    Pc.addPoint(disp[i].x,disp[i].y);
  }



  int num=1500;
  for(int i = 0;i<=num;i++){
    double x1=asin(un(dev));
    double y1=re(dev);
    double y2=ye(dev);
    double y3=gr(dev);
    double y4=bl(dev);
    double y5=vi(dev);
    double t1 = the(dev);
    double t2 = the(dev);
    double t3 = the(dev);
    double t4 = the(dev);
    double t5 = the(dev);
    double psi1 = 4*asin(sin(x1)/Pc(y1))-2*x1;
    double h1 = tan(psi1);
    prof1.addPoint(h1*sin(t1),h1*cos(t1));
    double psi2 = 4*asin(sin(x1)/Pc(y2))-2*x1;
    double h2 = tan(psi2);
    prof2.addPoint(h2*sin(t2),h2*cos(t2));
    double psi3 = 4*asin(sin(x1)/Pc(y3))-2*x1;
    double h3 = tan(psi3);
    prof3.addPoint(h3*sin(t3),h3*cos(t3));
    double psi4 = 4*asin(sin(x1)/Pc(y4))-2*x1;
    double h4 = tan(psi4);
    prof4.addPoint(h4*sin(t4),h4*cos(t4));
    double psi5 = 4*asin(sin(x1)/Pc(y5))-2*x1;
    double h5 = tan(psi5);
    prof5.addPoint(h5*sin(t5),h5*cos(t5));
  }

 

  view.add(&prof1);
   view.add(&prof2);
  view.add(&prof3);
   view.add(&prof4);
  view.add(&prof5);
  

  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << ""
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << ""
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << ""
	       << PlotStream::EndP();
  
  
  
  
   
   



  view.show();
  window.show();
  app.exec();
  return 1;

}

