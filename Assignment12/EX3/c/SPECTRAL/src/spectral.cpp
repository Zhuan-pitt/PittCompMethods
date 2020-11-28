#include <QatGenericFunctions/Variable.h>
#include <QatGenericFunctions/Parameter.h>
#include <QatGenericFunctions/Square.h>
#include <QatGenericFunctions/Sqrt.h>
#include <QatGenericFunctions/Exp.h>
#include <QatDataAnalysis/Hist1D.h>
#include "QatDataAnalysis/Hist1D.h" 
#include "QatGenericFunctions/Variable.h"
#include "QatPlotting/PlotHist1D.h" 
#include "QatDataModeling/HistChi2Functional.h"
#include <QatDataModeling/MinuitMinimizer.h>
#include <QatPlotWidgets/PlotView.h>
#include <QatPlotWidgets/MultipleViewWindow.h>
#include <QatPlotting/PlotStream.h>
#include <QatPlotting/PlotHist1D.h>
#include <QatPlotting/PlotFunction1D.h>
#include <QatPlotting/PlotProfile.h>
#include <QatPlotting/PlotKey.h>
#include <QApplication>
#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QFont>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

typedef std::vector<double> Data;


int main (int argc, char **argv) {
using namespace std;
using namespace Genfun;
  int nbin=300;
  double r_min = 80;
  double r_max = 130;
  Data da;
  int i =0;
  // Hist1D his(nbin,0,range);
  Hist1D hist(nbin,r_min,r_max);
  
    ifstream infile("./data02.dat");  
    string temp;
    if (!infile.is_open())
    {  
        cout<<"can not open the file \n"<<endl;
        return -1;
    }
    while(getline(infile,temp))  
    {   
        hist.accumulate(stod(temp));
    }
    infile.close();


  
  PlotHist1D phist = hist;

  Parameter psigma1("sigma1",hist.variance(),0.01,1);
  Parameter pmu1("mu1",103,hist.min(),hist.max());
  
  Parameter psigma2("sigma2",hist.variance(),0.01,1);
  Parameter pmu2("mu2",105,hist.min(),hist.max());
  
  Parameter psigma3("sigma3",hist.variance(),0.01,1);
  Parameter pmu3("mu3",103,hist.min(),hist.max());
  
  Parameter psigma4("sigma4",hist.variance(),0.01,1);
  Parameter pmu4("mu4",105,hist.min(),hist.max());
  
  Parameter pfra1("fra1",0.4,0,1);
  Parameter pfra2("fra2",0.4,0,1);
  Parameter pfra3("fra3",0.4,0,1);

  Variable X;
  Exp exp;
  GENFUNCTION g1 = 1./(psigma1*2.506628275)*exp(-(X-pmu1)*(X-pmu1)/(2*psigma1*psigma1));
  GENFUNCTION g2 = 1./(psigma2*2.506628275)*exp(-(X-pmu2)*(X-pmu2)/(2*psigma2*psigma2));
  GENFUNCTION l1 = 1./(3.14159265)*(psigma3/((X-pmu3)*(X-pmu3)+psigma3*psigma3));
  GENFUNCTION l2 = 1./(3.14159265)*(psigma4/((X-pmu4)*(X-pmu4)+psigma4*psigma4));
  GENFUNCTION dist = pfra1*pfra2*pfra3*g1+(1-pfra1)*pfra2*pfra3*g2
                      +(1-pfra1)*(1-pfra2)*pfra3*l1+(1-pfra1)*(1-pfra2)*(1-pfra3)*l2;

  HistChi2Functional objectiveFunction(&hist);
  GENFUNCTION f = hist.sum()*dist;
  //  GENFUNCTION f = hist.sum()*lorentzian;
  cout<<hist.sum()<<endl;
  bool verbose=true;
  MinuitMinimizer minimizer(verbose); 
  minimizer.addParameter(&psigma1); 
  minimizer.addParameter(&pmu1); 
  minimizer.addParameter(&psigma2); 
  minimizer.addParameter(&pmu2); 
    minimizer.addParameter(&psigma3); 
  minimizer.addParameter(&pmu3); 
  minimizer.addParameter(&psigma4); 
  minimizer.addParameter(&pmu4); 
  minimizer.addParameter(&pfra1); 
  minimizer.addParameter(&pfra2); 
  minimizer.addParameter(&pfra3); 
  minimizer.addStatistic(&objectiveFunction,&f); 
  minimizer.minimize();
  
  PlotFunction1D pguassian(f*1./nbin*(r_max-r_min));


  QApplication     app(argc,argv);
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  quitAction->setShortcut(QKeySequence("q"));
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));

  // The following code sets the scale for a linear plot:
  PRectF rect;
  rect.setXmin(95);
  rect.setXmax(110);
  rect.setYmin(0);
  rect.setYmax(300);
  PlotView view(rect);
  window.setCentralWidget(&view);
  
  

  
 
  // And we add them to the plotter:
  view.add(&pguassian);
  view.add(&phist);
  
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << PlotStream::Normal()
	      <<"Distribution Density"
	      << PlotStream::EndP();
  
  // Label the x-axis
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "x"
	       << PlotStream::EndP();

  // Label the y-axis.
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "\u03c1(x)"
	       << PlotStream::EndP();
  
  // Show the window and start user interaction:
  window.show();
  app.exec();
 
  return 1;

}

