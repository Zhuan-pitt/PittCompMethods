#include<iostream>
#include <sstream>

int main (int argc, char const *argv[])
{   
    std::istringstream stream_a(argv[1]);
    double a ;
    stream_a >> a;
    std::istringstream stream_b(argv[2]);
    double b ;
    stream_b >> b;
    std::cout << a<<"+"<<b<<'='<<a+b << " ";
    std::cout << std::endl;
    return 0;
}