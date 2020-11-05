#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include <mutex> 
#include <thread>   
#include <random>
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatGenericFunctions/ASin.h"
#include "QatGenericFunctions/Sin.h"
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
#include <vector> 


void rainbow(int seed, Hist1D *result, double y) 
{
  
  std::mt19937 engine(seed);
  std::uniform_real_distribution<double> un(0,1);
  std::exponential_distribution<double> ex(1/log(2));
  int nbin=200;
  int num =6000000;
  double range = 1.5708;
  Hist1D his(nbin,0,range);
  for (int i=1;i<num;i++){
  double x = asin(un(engine));

  double n =ceil(ex(engine));

  double th = (1-n)*3.14159266+2*(n+1)*asin(sin(x)/y)-2*x+3.14159265;
  th = pow(-1,n+1)*(th-floor(th/(3.14159265*2))*2*3.14159265-3.14159265);
  
  his.accumulate(th,1./(num*1.5708)*200);
  
  }
  *result = his;
}



int main (int argc, char **argv) {
    using namespace std;
  using namespace Genfun;
      struct PPoint
{
  double x;
  double y;
};

size_t NPROC=thread::hardware_concurrency();
std::vector<std::thread> tVector;
Hist1D his(200,0,1.5708);
std::vector<Hist1D> rVector={his,his,his,his};
  

std::vector<PPoint> disp={{400,1.339},{450,1.337},{500,1.335},{550,1.333},{600,1.332},
{650,1.331},{700,1.331},{750,1.331}};

  double range = 1.5708;

  
 for (size_t i=0;i<NPROC;i++) {
    tVector.push_back(std::thread(rainbow,i,&rVector[i],disp[2*i].y));
  }
  
   for (size_t i=0;i<NPROC;i++) {
    tVector[i].join();
   
  }




  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax(range);
  rect.setYmin(0);
  rect.setYmax(10);
  
 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);




 PlotHist1D phis = rVector[0];
  PlotHist1D phis2 = rVector[1];
   PlotHist1D phis3 = rVector[2];
    PlotHist1D phis4 = rVector[3];
   PlotProfile prof1;
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("red");
    phis4.setProperties(prop);
  }
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("orange");
    phis3.setProperties(prop);
  }
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("green");
    phis2.setProperties(prop);
  }
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("blue");
    phis.setProperties(prop);
  }
 view.add(&phis);
view.add(&phis2);
 view.add(&phis3);
 view.add(&phis4);
 
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Probability Density Distribution"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "\u03C6"
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

