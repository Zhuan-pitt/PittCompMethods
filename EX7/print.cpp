#include<iostream>
#include <sstream>
#include "libPlus.h"
int print (Control *control){
    std::cout << control->a<<"+"<<control->b<<'='<<control->c << " ";
    std::cout << std::endl;
    return 0;
}