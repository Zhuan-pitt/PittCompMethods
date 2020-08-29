#include<iostream>
#include <sstream>
#include"libPlus.h"
Control *parse(int argc, char ** argv){
    Control *control=NULL;
    control =new Control; 
    control->a=0; 
    control->b=0; 
    { std::istringstream stream(argv[1]); 
    if (!(stream >> control->a)) return control; } 
    { std::istringstream stream(argv[2]); 
    if (!(stream >> control->b)) return control; }
    return control;
}