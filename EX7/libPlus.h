#ifndef _Plus_H_ 
#define _Plus_H_


struct Control { 
    double a; double b; double c;
    }; // // Parse the command line:

// 
Control *parse (int argc, char ** argv);
void add(Control *control); 
int print(Control *control);

#endif