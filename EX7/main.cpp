#include "libPlus.h"
int main (int argc, char **argv)
{  
    Control *control = parse(argc, argv); 
    add(control); 
    print(control); 
    return 0;    
}