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

 
 Variable X;
  Exp exp;

  int nbin=300;
  double r_min = 0;
  double r_max = 150;
  Data da;
  // Hist1D his(nbin,0,range);
  Hist1D hist(nbin,r_min,r_max);
  int i =0;
    ifstream infile("./data04.dat");  
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



  Parameter psigma1("sigma1",0.4,0.01,1);
  Parameter pmu1("mu1",103,90,100);
  
  Parameter psigma2("sigma2",0.4,0.01,1);
  Parameter pmu2("mu2",103,100,110);
  Parameter pfra1("fra1",0.4,0,10);

 GENFUNCTION l1 = 1./(3.14159265)*(psigma1/((X-pmu1)*(X-pmu1)+psigma1*psigma1));
  GENFUNCTION l2 = 1./(3.14159265)*(psigma2/((X-pmu2)*(X-pmu2)+psigma2*psigma2));
  GENFUNCTION bb =0.0000053468*X*X*X*1/(exp(X/12.716)-1);
  GENFUNCTION lorentzian = pfra1*l1+(1-pfra1)*l2;
  


  HistChi2Functional objectiveFunction(&hist);
  // GENFUNCTION f = hist.sum()*guassian;
   GENFUNCTION f = (hist.sum()*0.09442)*lorentzian+hist.sum()*bb;
  cout<<hist.sum()<<endl;
  bool verbose=true;
  MinuitMinimizer minimizer(verbose); 
  minimizer.addParameter(&psigma1); 
  minimizer.addParameter(&pmu1); 
  minimizer.addParameter(&psigma2); 
  minimizer.addParameter(&pmu2); 
  minimizer.addParameter(&pfra1); 
  // minimizer.addParameter(&pfra2); 
  // minimizer.addParameter(&kT);
  // minimizer.addParameter(&c);
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
  rect.setXmin(0);
  rect.setXmax(150);
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

