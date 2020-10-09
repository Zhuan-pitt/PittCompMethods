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

  GENFUNCTION p0 = H0*pow(pi,-0.25)/(sqrt(pow(2,0)*fac(0)))*exp(-X*X/2);
  GENFUNCTION p1 = H1*pow(pi,-0.25)/(sqrt(pow(2,1)*fac(1)))*exp(-X*X/2);
  GENFUNCTION p2 = H2*pow(pi,-0.25)/(sqrt(pow(2,2)*fac(2)))*exp(-X*X/2);
  GENFUNCTION p3 = H3*pow(pi,-0.25)/(sqrt(pow(2,3)*fac(3)))*exp(-X*X/2);
  GENFUNCTION p4 = H4*pow(pi,-0.25)/(sqrt(pow(2,4)*fac(4)))*exp(-X*X/2);

 

  GaussHermiteRule rule3(argc==2 ? std::stoi(argv[1]):6);
  GaussIntegrator inte3(rule3);

 

struct FuncSet
{
  GENFUNCTION f;
};

std::vector<FuncSet> num={{p0},{p1},{p2},{p3},{p4}};
  
Eigen::MatrixXd Ax(5,5); 
Eigen::MatrixXd Ax2(5,5); 
Eigen::MatrixXd Ad(5,5); 
Eigen::MatrixXd Ad2(5,5);
Eigen::MatrixXd Ah(5,5);  
for(int i =0;i<=4;i++){
  for (int j=0;j<=4;j++){

    // matrix representation for x 
    Ax(i,j)=inte3(num[i].f*X*num[j].f);
    // matrix representation for x^2
    Ax2(i,j)=inte3(num[i].f*X*X*num[j].f);
    // matrix representation for D
    Ad(i,j)=inte3(num[i].f*num[j].f.prime());
    // matrix representation for D^2
    Ad2(i,j)=inte3(num[i].f*num[j].f.prime().prime());
  }
}
  std::cout<<"The matrix representation for x is "<<std::endl;
  std::cout<<Ax<<std::endl;

  std::cout<<"\n The matrix representation for x^2 is "<<std::endl;
  std::cout<<Ax2<<std::endl;
  std::cout<<"\n The matrix representation for D is "<<std::endl;
  std::cout<<Ad<<std::endl;
  std::cout<<"\n The matrix representation for D^2 is "<<std::endl;
  std::cout<<Ad2<<std::endl;
  std::cout<<"\n The matrix representation for Hamiltonian is "<<std::endl;
  std::cout<<(Ax2-Ad2)/2.<<std::endl;





  return 1;
}


