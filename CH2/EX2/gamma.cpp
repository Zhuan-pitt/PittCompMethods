#include <iostream>
#include <math.h>

int main (int argc, char ** argv) { 
    int arraylength =14;
    //Method 1: gamma=1/sqrt(1-beta^2)
    double beta[arraylength];
    double gam1[arraylength];
    //Method 2: gamma=1/sqrt((2-epsilon)epsilon)
    double gam2[arraylength];
    for (int i=0;i<arraylength;i++){
        beta[i]=1-pow(10,-i-1);
        gam1[i]=1/sqrt(1-pow(beta[i],2));
        gam2[i]=1/sqrt((2-pow(10,-i-1))*pow(10,-i-1));

        std::cout<<"beta=1-10^("<<-i-1<<"), gamma1="<<gam1[i]<<", gamma2="<<gam2[i];
        std::cout<<std::endl;
    }
    //std::cout<<beta[8]-beta[9]<<" ";
}