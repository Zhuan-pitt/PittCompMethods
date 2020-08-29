#include<cmath>
#include<iostream>
#include <sstream>

double exp_tylor(double b){
    double x=1;
    double c=1;
    for (double i=1;i<=50;i++){
        c = c*b/i;
        x=x+c;
    }
    return x;
}

int main (int argc, char const *argv[])
{
    std::cout << "x" << "     "<<"exp(x)"<< '\n';
   for (double i = -10; i<=10; i=i+2)
   {
     std::cout << i << "   " <<exp_tylor(i) << "\n";
   }
    std::cout << std::endl;
    return 0;
}