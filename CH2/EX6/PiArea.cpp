#include <complex>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
typedef std::complex<double> Complex;
int main () {
  // 1. Just print out the macro:
  std::cout << std::setprecision(16) << M_PI << std::endl;

  // 2. From the area of inner inscribed polygons.  

  Complex x0=1.0;
  Complex x1(1.0/2.,sqrt(3.0)/2.0);
  unsigned int nsides=6;
  while (nsides < std::numeric_limits<int>::max()) {

   
    double area = x1.imag()*0.5*1;//Area of isoceles triangles;
    double approx=nsides*area;
    std::cout << "Sides " << nsides << "; approx=" << std::setprecision(16) << approx << std::endl;

    x1=(x1+x0)/abs(x1+x0);
    nsides *=2; 
  }
}