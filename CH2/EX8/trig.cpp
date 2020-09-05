#include <complex>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
typedef std::complex<double> Complex;

//sin(ix)=i*sinh(x); cos(ix)=cosh(x)

int main(int argc, char **argv){
    std::istringstream stream(argv[1]);
    double x ;
    stream >> x;
    Complex I(0,1);
    Complex IX(0,x);
    std::cout<< "sin(i"<<x<<") = "<<sin(IX).imag()<<std::endl;
    std::cout<< "sinh("<<x<<") = "<<sinh(x)<<std::endl;

    std::cout<< "cos(i"<<x<<") = "<<cos(IX).real()<<std::endl;
    std::cout<< "cosh("<<x<<") = "<<cosh(x)<<std::endl;
    
    
    return 0;
}

