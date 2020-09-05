#include <complex>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
typedef std::complex<double> Complex;
// We set bar{h}/2m = 1
// In reigon I, we have phi(x)=Ae^(ik_1x)+Be^(ik_1x)
// In reigon II, we have phi(x)=Ae^(ik_2x)+Be^(ik_2x)

int main (int argc, char **argv){
    std::istringstream streamE(argv[1]);
    std::istringstream streamV(argv[2]);
    double E;
    double V;
    streamE>>E;
    streamV>>V;//Obetain energy and potential

    //calculate the wave vectors
   
        Complex k1=sqrt(E);
        Complex k2=0;
        if (V<=E){
           Complex k(sqrt(E-V),0);
           k2=k+k2;
        }
        else{
            Complex k(0,sqrt(V-E));
            k2=k+k2;
        }
        

    //boudary conditions:
    // Let x =A/C, y = B/C
    // x + y = 1
    // i*k1*x -i*k1*y =ik2
    Complex I(0,1);
    Complex x = (k1+k2)/(2.*k1);
    Complex y = (k1-k2)/(2.*k1);

   
   
    //reflection rate R = |B/A^2
    double R = norm(y/x);
    double T = 1-R;
     
    std::cout<<"\u03A6(x) = "<<x<<"*exp(i*"<<k1<<"x)+"<<y<<"*exp(-i*"<<k1<<"x), for x<0"<<std::endl;

    std::cout<<"\u03A6(x) = "<<"exp(i*"<<k2<<"x), for x>0"<<std::endl;
    std::cout<<"The relection rate R = "<<R<<std::endl;
    std::cout<<"The transmission rate T = "<<T<<std::endl;




    return 0;
}