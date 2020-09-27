#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/GaussIntegrator.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/FixedConstant.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Abs.h"
#include "QatGenericFunctions/GaussQuadratureRule.h"
#include "Eigen/Dense"


double fac(int n){
  if (n == 0){
    return 1.;
  }
  else{
    double f=1.;
    for (int i = 1;i<=n;i++){
        f=f*i;
    } 
    return f;
  }
}

int main (int argc, char **argv) {

  using namespace Genfun;
  double pi = 3.1415926535897932;
  Variable X;
  //Hermit polynomials:
  Exp exp;
  GENFUNCTION H0 = 1+X-X;
  GENFUNCTION H1 = 2*X;
  GENFUNCTION H2 = 4*X*X-2;
  GENFUNCTION H3 = 8*X*X*X-12*X;
  GENFUNCTION H4 = 2*X*H3-6*H2;
  GENFUNCTION H5 = 2*H4*X-8*H3;

  GENFUNCTION p0 = H0*pow(pi,-0.25)/(sqrt(pow(2,0)*fac(0)))*exp(-X*X/2);
  GENFUNCTION p1 = H1*pow(pi,-0.25)/(sqrt(pow(2,1)*fac(1)))*exp(-X*X/2);
  GENFUNCTION p2 = H2*pow(pi,-0.25)/(sqrt(pow(2,2)*fac(2)))*exp(-X*X/2);
  GENFUNCTION p3 = H3*pow(pi,-0.25)/(sqrt(pow(2,3)*fac(3)))*exp(-X*X/2);
  GENFUNCTION p4 = H4*pow(pi,-0.25)/(sqrt(pow(2,4)*fac(4)))*exp(-X*X/2);
  GENFUNCTION p5 = H5*pow(pi,-0.25)/(sqrt(pow(2,5)*fac(5)))*exp(-X*X/2);

 

  GaussHermiteRule rule3(argc==2 ? std::stoi(argv[1]):6);
  GaussIntegrator inte3(rule3);

 

struct FuncSet
{
  GENFUNCTION f;
};

std::vector<FuncSet> num={{p0},{p1},{p2},{p3},{p4},{p5}};
  
Eigen::MatrixXd A(6,6); 
for(int i =0;i<=5;i++){
  for (int j=0;j<=5;j++){
    A(i,j)=inte3(num[i].f*num[j].f);
  }
}
  
  std::cout<<A<<std::endl;




  return 1;
}

