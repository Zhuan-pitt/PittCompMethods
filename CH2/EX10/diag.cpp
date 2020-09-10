#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <complex>
#include <Eigen/Dense>
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


    Complex delta0 = pow(a,2)-3.*b;
    Complex delta1 = 2.*pow(a,3)-9.*a*b+27.*c;

    Complex ci(-0.5,sqrt(3.)/2.);
    Complex ci_t(-0.5,-sqrt(3.)/2.);

    Complex C=pow((delta1+pow(pow(delta1,2)-4.*pow(delta0,3),1/2.))/2.,1/3.);


    Complex x1 = -1./3.*(a+C+delta0/C) ;
    Complex x2 = -1./3.*(a+ci*C+ci_t*delta0/C) ;
    Complex x3 = -1./3.*(a+ci_t*C+ci*delta0/C) ;
    
    //std::cout<<x1<<" "<<x2<<" "<<x3<<std::endl;

    Vector3cd Eig;
    Eig << x1, x2, x3 ;

    std::cout<<"The eigenvalue of matrix A "<< " is "<< Eig.transpose()<<std::endl;
    Matrix3cd Eigvec;
    for (int i = 0; i<=2; i++){
        Matrix3cd B=A;
        B(0,0)=B(0,0)-Eig(i);
        B(1,1)=B(1,1)-Eig(i);
        B(2,2)=B(2,2)-Eig(i);

        Matrix2cd b1;
        Matrix2cd b2;
        Matrix2cd b3;
        Matrix2cd b4;

        b1 << B(0,0),B(0,1),
              B(1,0),B(1,1);
        b2 << B(0,1),B(0,2),
              B(1,1),B(1,2);
        b3 << B(0,0),B(0,1),
              B(2,0),B(2,1);
        b4 << B(0,1),B(0,2),
              B(2,1),B(2,2);

        Complex de = b1.determinant()*b4.determinant()-b2.determinant()*b3.determinant();
        

        if (abs(de)<pow(10,-8)){
            Eigvec(i,0)=1;
            Eigvec(i,1)=b1.determinant()/b2.determinant();
            Eigvec(i,2)=-(B(0,0)*Eigvec(i,0)+B(0,2)*Eigvec(i,2))/B(0,1);
        }
        else{
            Eigvec(i,0)=0;
            Eigvec(i,1)=0;
            Eigvec(i,2)=1;
        }

        
    }

    //normalize the eigenvectors

    Vector3cd v1;
    Vector3cd v2;
    Vector3cd v3;

    v1<<Eigvec(0,0),Eigvec(1,0),Eigvec(2,0);
    v2<<Eigvec(0,1),Eigvec(1,1),Eigvec(2,1);
    v3<<Eigvec(0,2),Eigvec(1,2),Eigvec(2,2);

    v1.normalize();
    
    v2=v2-v2.dot(v1)*v1;
    v2.normalize();

    v3=v3-v3.dot(v2)*v2-v3.dot(v1)*v1;
    v3.normalize();

    std::cout<<"The eigenvector is: v1 = "<<v1.transpose()<<"\n"
    <<" v2 = "<<v2.transpose()<<"\n"<<" v3 = "<<v3.transpose()<<std::endl;


    return 0;
}

