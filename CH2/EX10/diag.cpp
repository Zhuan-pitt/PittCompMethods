#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <complex>
#include "/Users/lizhuan/Desktop/CM/eigen/Eigen/Dense"
using namespace Eigen;
typedef std::complex<double> Complex;


int main (int argc, char **argv)
{
       
    Matrix3cd A; 
    A<< 0.333333 ,-0.244017 ,0.910684,
        0.910684 ,0.333333 ,-0.244017,
        -0.244017, 0.910684 ,0.333333;
   // std::cout<<A(2,1)<<std::endl;
    //secular equation for 3*3 matrix can be written as:
    //-x^3+ax^2+bx+c=0
    //c=det(A), b=-det(A(1,2;1,2))-det(A(2,3;2,3))-det(A(1,3;1,3))
    //a=A(1,1)+A(2,2)+A(3,3)
    Complex a = A(0,0)+A(1,1)+A(2,2);
    Complex c = A.determinant();
    Matrix2cd B;
    B<<A(0,0),A(0,1),
        A(1,0),A(1,1);
    Complex b= -B.determinant();
    B<<A(0,0),A(0,2),
        A(2,0),A(2,2);
    b= b-B.determinant();
    B<<A(1,1),A(1,2),
        A(2,1),A(2,2);
    b= b-B.determinant();
    // discriminant 
    a=-a;b=-b;c=-c;


    Complex deta0 = pow((b/3.-pow(a,2)/9.),3);
    Complex deta1 = a*b/6. - pow(a,3)/27.-c/2.;

    Complex ci(-0.5,sqrt(3)/2.);
    Complex ci_t(-0.5,-sqrt(3)/2.);

    Complex u1 =pow(deta1+pow(pow(deta1,2)+deta0,0.5),1./3.);

    Complex u2 =pow(deta1-pow(pow(deta1,2)+deta0,0.5),1./3.);

    Complex x1 = -a/3. + u1+u2 ;
    Complex x2 = -a/3. + ci*u1 +ci_t*u2;
    Complex x3 = -a/3. + ci*u2 +ci_t*u1;
    
    std::cout<<a<<" "<<b<<" "<<c<<std::endl;
    std::cout<<x1<<" "<<x2<<" "<<x3<<std::endl;



    return 0;
}

