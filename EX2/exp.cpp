#include<cmath>
#include<iostream>
#include <sstream>

int main (int argc, char const *argv[])
{
    std::istringstream stream(argv[1]);
    double a ;
    stream >> a;
    std::cout << exp(a) << " ";
    std::cout << std::endl;
    return 0;
}