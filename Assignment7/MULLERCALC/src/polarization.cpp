#include "JONESCALC/StokesVector.h"
#include "JONESCALC/MullerMatrix.h"
#include <iostream>
#include <string>
int main (int argc, char ** argv) {

  StokesVector v0(StokesVector::Horizontal);
  MullerMatrix PH(MullerMatrix::FastHorizontal);
  MullerMatrix PV(MullerMatrix::FastVertical);

  // Make a circular polarizer:
  MullerMatrix CP=PH*PV;
  StokesVector v1=CP*v0;

  std::cout << "Initial= " << v0 << std::endl;
  std::cout << "Filter= " << std::endl;
  std::cout << CP << std::endl;
  std::cout << "Final intensity= " << v1.magsq() << std::endl;
  std::cout << "Final polarization= " << v1*(1/sqrt(v1.magsq())) << std::endl;

  return 1;
}
