#include <iostream>
//#include <math.h>

int main (int argc, char ** argv) { 
    //The machine precision of float is 2^-23 = 1.2E-7
    double a =1;
    double b=1;
    int floatloopstop=0;
    for (int i=1;i<100;i++ ){
        double d = a+b;
        if (floatloopstop==0){
            float c=a+b;
            if(c==b){
                // If c==b, we can not distinguish the difference equal or smaller that a;
                // Therefore the precision is 2*a.
                std::cout<<"The precision of float datatype is "<<a*2<<std::endl;
                floatloopstop=1;   
            }
        }
        if(d==b){
                // If c==b, we can not distinguish the difference equal or smaller that a;
                // Therefore the precision is 2*a.
                std::cout<<"The precision of double datatype is "<<a*2<<std::endl;
            break;
        }
        a=a/2; 
    }
    //std::cout<< a <<" "<< a/2 <<" "<< a/4 ;
    //std::cout<< a/2 << " ";
}