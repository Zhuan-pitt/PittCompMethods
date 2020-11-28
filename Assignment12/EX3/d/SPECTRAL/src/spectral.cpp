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
  double r_min = 0;
  double r_max = 150;
  Data da;
  int i =0;
  // Hist1D his(nbin,0,range);
  Hist1D hist(nbin,r_min,r_max);
  
    ifstream infile("./data03.dat");  
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

  Parameter kT("kT",103,0,500);
  Parameter c("c",1,0,5);
  


  Variable X;
  Exp exp;
 GENFUNCTION bb = c*X*X*X*1/(exp(X/kT)-1);
  HistChi2Functional objectiveFunction(&hist);
  // GENFUNCTION f = hist.sum()*guassian;
  GENFUNCTION f = hist.sum()*bb;
  cout<<hist.sum()<<endl;
  bool verbose=true;
  MinuitMinimizer minimizer(verbose); 
  minimizer.addParameter(&kT);
  minimizer.addParameter(&c);
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

