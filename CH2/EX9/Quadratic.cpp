#include <complex>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
typedef std::complex<double> Complex;

Complex times(double a,Complex b){
    Complex ac(a,0);
    return a*b;
}

int main (int argc, char **argv)
{   
//This program is designed to solve quadratic equation ax^2+bx+c=0;
    std::istringstream streama(argv[1]);
    std::istringstream streamb(argv[2]);
    std::istringstream streamc(argv[3]);
    Complex b ;
    Complex a ;
    Complex c;

    streama >> a; 
    streamb >> b;
    streamc >> c;

    Complex x1= (-b+sqrt(b*b-times(4,a)*c))/(times(2,a));
    Complex x2= (-b-sqrt(b*b-times(4,a)*c))/(times(2,a));
    std::cout<< "x1 = "<< x1.real() <<"+(" <<x1.imag()<<"i), x2 = "<< x2.real() <<"+(" <<x2.imag()<<"i)";
  
    
    
    return 0;
}