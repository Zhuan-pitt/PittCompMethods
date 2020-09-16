#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/F1D.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <Eigen/Dense>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/CutBase.h"
#include "QatGenericFunctions/F2D.h"
#include "QatPlotting/PlotWave1D.h"
typedef std::complex<double> Complex;

class Window:public Cut<double> {
public:

  Window(double min, double max):Cut<double>(), min(min), max(max) {};

  virtual bool operator () (const double & x) const {
    return x>min && x<=max;
  }

  virtual Window *clone() const {
    return new Window(*this);
  }
private:
  double min;
  double max;
};

int main (int argc, char * * argv) {
  // solve the wave function from ex7
  
  double ka;
  std::cout<<"Please input the value of ka"<<std::endl;
  std::cin>>ka;
  
    //Set bar{h}/2m==1
  double v1 = 1.5; //v1=V0/E
  Complex n1;
  if(v1>1){
  n1=Complex(0,sqrt(v1-1)); 
  }//index of refraction in region I&III
  else{
  n1=Complex(sqrt(1.0-v1),0);
  }
  
  double v2 = 2*v1; //v1=2*V0/E
  Complex n2;
  if(v2>1){
  n2=Complex(0,sqrt(v2-1)); 
  }
  else{
  n2=Complex(sqrt(1.0-v2),0);
  } //index of refraction in region II
  double k = 1.0;// k =sqrt(E)

  std::cout<<n2<<std::endl;

  double a=ka;
  
  Complex I(0,1.0);

  Eigen::VectorXcd Y(8); 
  Y(0)=-exp(-I*k*2.*a);
  
  Eigen::MatrixXcd A(8,8); 
  A(0,0)=exp(2.*a*I*k); A(0,1)=-exp(-2.*a*I*n1*k); A(0,2)=-exp(2.*a*I*n1*k);A(0,3)=0;
  A(0,4)=0;A(0,5)=0;A(0,6)=0;A(0,7)=0;//first row

  Y(1)=-I*k*exp(-I*k*2.*a);
  A(1,0)=-I*k*exp(2.*a*I*k); A(1,1)=-I*n1*k*exp(-2.*a*I*n1*k); A(1,2)=I*n1*k*exp(2.*a*I*n1*k);A(1,3)=0;
  A(1,4)=0;A(1,5)=0;A(1,6)=0;A(1,7)=0;//second row

  Y(2)=0;
  A(2,0)=0;A(2,5)=0;
  A(2,1)=-exp(-a*I*n1*k);A(2,2)=-exp(I*k*n1*a);
  A(2,3)=exp(-I*n2*k*a);A(2,4)=exp(I*n2*k*a);A(2,6)=0;A(2,7)=0;//third row

  Y(3)=0;
  A(3,0)=0;A(3,5)=0;
  A(3,1)=-I*n1*k*exp(-a*I*n1*k);A(3,2)=I*k*n1*exp(I*k*n1*a);
  A(3,3)=I*n2*k*exp(-I*n2*k*a);A(3,4)=-I*n2*k*exp(I*n2*k*a);A(3,6)=0;A(3,7)=0;//forth row

  Y(4)=0;
  A(4,0)=0;A(4,1)=0;
  A(4,5)=-exp(a*I*n1*k);A(4,6)=-exp(-I*k*n1*a);
  A(4,3)=exp(I*n2*k*a);A(4,4)=exp(-I*n2*k*a);A(4,2)=0;A(4,7)=0;//fifth row

  Y(5)=0;
  A(5,0)=0;A(5,1)=0;
  A(5,5)=-I*n1*k*exp(a*I*n1*k);A(5,6)=I*k*n1*exp(-I*k*n1*a);
  A(5,3)=I*n2*k*exp(I*n2*k*a);A(5,4)=-I*n2*k*exp(-I*n2*k*a);A(5,2)=0;A(5,7)=0;//fifth row

  Y(6)=0;
  A(6,5)=exp(2.*a*I*n1*k);A(6,6)=exp(-I*k*n1*2.*a);
  A(6,7)=-exp(2.*I*k*a);A(6,0)=0;A(6,2)=0;A(6,3)=0;A(6,1)=0;A(6,4)=0;

  Y(7)=0;
  A(7,5)=I*n1*k*exp(2.*a*I*n1*k);A(7,6)=-I*n1*k*exp(-I*k*n1*2.*a);
  A(7,7)=-I*k*exp(2.*I*k*a);A(7,0)=0;A(7,2)=0;A(7,3)=0;A(7,1)=0;A(7,4)=0;




   Eigen::VectorXcd BCDEFGHJ=A.inverse()*Y;

Complex b;
Complex c;
Complex d;
Complex e;
Complex f;
Complex g;
Complex h;
Complex j;

b =BCDEFGHJ(0);
c =BCDEFGHJ(1);
d =BCDEFGHJ(2);
e =BCDEFGHJ(3);
f =BCDEFGHJ(4);
g =BCDEFGHJ(5);
h =BCDEFGHJ(6);
j =BCDEFGHJ(7);


//Plot 2d graph


  // This is example code demonstrating how to visualize functions
  // using the QAT libraries.

  // It plots f(x) where f(x) is a function defined just above:


  // This part is "boilerplate" from the Qt package.  It sets up a window
  // which is part of the graphical user interface.  It adds a toolbar
  // with a "Quit" button, and the button has a keyboard accerator: the
  // q key can be pressed to quit the application. Interested users
  // can consult the Qt documentation for more information. 
  
  QApplication     app(argc,argv);
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  quitAction->setShortcut(QKeySequence("q"));
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));

  // The following code sets the scale for a linear plot:
  PRectF rect;
  rect.setXmin(-3);
  rect.setXmax( 3.0);
  rect.setYmin(-3);
  rect.setYmax( 3);
  
  // Now create a "PlotView" and put it in the window.  This is a set of
  // axes onto which one can plot functions and draw other objects. 
  PlotView view(rect);
  window.setCentralWidget(&view);
  using namespace Genfun;
  Variable X1(0,2),T(1,2);
  
  Cos cos;
  Sin sin;
  Exp exp;

GENFUNCTION FL = cos(T)*(cos(k*X1)+b.real()*cos(k*X1)+b.imag()*sin(k*X1))
                +sin(T)*(-sin(k*X1)+b.real()*sin(k*X1)-b.imag()*cos(k*X1));

GENFUNCTION IFL = cos(T)*(sin(k*X1)+b.imag()*cos(k*X1)-b.real()*sin(k*X1))
                +sin(T)*(cos(k*X1)+b.real()*cos(k*X1)+b.imag()*sin(k*X1));



GENFUNCTION FM1 = cos(T)*(c.real()*exp(-k*n1.imag()*X1)+d.real()*exp(k*n1.imag()*X1))+
                  -sin(T)*(c.imag()*exp(-k*n1.imag()*X1)+d.imag()*exp(k*n1.imag()*X1));
GENFUNCTION IFM1 = cos(T)*(c.imag()*exp(-k*n1.imag()*X1)+d.imag()*exp(k*n1.imag()*X1))
                  +sin(T)*(c.real()*exp(-k*n1.imag()*X1)+d.real()*exp(k*n1.imag()*X1));


GENFUNCTION FM2 = cos(T)*(e.real()*exp(-k*n2.imag()*X1)+f.real()*exp(k*n2.imag()*X1))+
                  -sin(T)*(e.imag()*exp(-k*n2.imag()*X1)+f.imag()*exp(k*n2.imag()*X1));
GENFUNCTION IFM2 = cos(T)*(e.imag()*exp(-k*n2.imag()*X1)+f.imag()*exp(k*n2.imag()*X1))
                  +sin(T)*(e.real()*exp(-k*n2.imag()*X1)+f.real()*exp(k*n2.imag()*X1));
           


GENFUNCTION FM3 =  cos(T)*(g.real()*exp(-k*n1.imag()*X1)+h.real()*exp(k*n1.imag()*X1))+
                  -sin(T)*(g.imag()*exp(-k*n1.imag()*X1)+h.imag()*exp(k*n1.imag()*X1));
GENFUNCTION IFM3 =  cos(T)*(g.imag()*exp(-k*n1.imag()*X1)+h.imag()*exp(k*n1.imag()*X1))
                  +sin(T)*(g.real()*exp(-k*n1.imag()*X1)+h.real()*exp(k*n1.imag()*X1));
 



  GENFUNCTION FR = cos(T)*(j.real()*cos(k*X1)-j.imag()*sin(k*X1))
                  -sin(T)*(j.real()*sin(k*X1)+j.imag()*cos(k*X1));
  GENFUNCTION IFR = sin(T)*(j.real()*cos(k*X1)-j.imag()*sin(k*X1))
                  +cos(T)*(j.real()*sin(k*X1)+j.imag()*cos(k*X1));


  // Here we make plots out of our function, first by adapting to an F1D
  // and then by adapting to a PlotFunction1D:
 const Cut<double> & wl    =Window(-3,-2*ka);
 const Cut<double> & wm1    =Window(-2*ka,-1*ka);
 const Cut<double> & wm2    =Window(-1*ka,ka);
 const Cut<double> & wm3    =Window(ka,2*ka);
 const Cut<double> & wr    =Window(2*ka,3);
 

 PlotWave1D pFL(FL,wl);
 PlotWave1D pFM1(FM1,wm1);
 PlotWave1D  pFM2(FM2,wm2);
 PlotWave1D  pFM3(FM3,wm3);
 PlotWave1D  pFR(FR,wr);


PlotWave1D pIFL(IFL,wl);
 PlotWave1D pIFM1(IFM1,wm1);
 PlotWave1D  pIFM2(IFM2,wm2);
 PlotWave1D  pIFM3(IFM3,wm3);
 PlotWave1D  pIFR(IFR,wr);

int index;
std::cout<<"choose the part you want to plot"<<"\n"<<"1. real part"<<"\n"<<"2. imaginary part"<<std::endl;
std::cin>>index;

  // And we add them to the plotter:
  if (index==1){
  view.add(&pFL);
  view.add(&pFM1);
  view.add(&pFM2);
  view.add(&pFM3);
  view.add(&pFR);
  
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Real part of wave funciton"
	      << PlotStream::EndP();
  
  // Label the x-axis
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "x"
	       << PlotStream::EndP();
  }
  else{
    view.add(&pIFL);
  view.add(&pIFM1);
  view.add(&pIFM2);
  view.add(&pIFM3);
  view.add(&pIFR);
  
  // Give the plot a title:
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "Imaginary part of wave funciton"
	      << PlotStream::EndP();
  
  // Label the x-axis
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "x"
	       << PlotStream::EndP();
  }
  
  
  
  // Show the window and start user interaction:
  window.show();
  app.exec();







  return 1;
}


