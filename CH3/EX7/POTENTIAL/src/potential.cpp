#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <Eigen/Dense>
typedef std::complex<double> Complex;

int main (int argc, char * * argv) {


    //Set bar{h}/2m==1
  double v1 = .8; //v1=V0/E
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

  double a=1;
  
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
//std::cout<<Y<<" \n  "<<A<<"\n "<<BCDEFGHJ<<std::endl;
  double R = norm(BCDEFGHJ(0));
  double T = norm(BCDEFGHJ(7));

std::cout<<"The coefficients for solution are"<<
"a = 1"<<"\n"<<
"b = "<<BCDEFGHJ(0)<<"\n"<<
"c = "<<BCDEFGHJ(1)<<"\n"<<
"d = "<<BCDEFGHJ(2)<<"\n"<<
"e = "<<BCDEFGHJ(3)<<"\n"<<
"f = "<<BCDEFGHJ(4)<<"\n"<<
"g = "<<BCDEFGHJ(5)<<"\n"<<
"h = "<<BCDEFGHJ(6)<<"\n"<<
"j = "<<BCDEFGHJ(7)<<"\n"<<std::endl;

std::cout<<"The reflection rate R = "<<R<<"\n"
<<"The transmission rate = "<<T<<std::endl;





  return 1;
}

