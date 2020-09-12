#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <complex>
#include <Eigen/Dense>
using namespace Eigen;

int main (int argc, char **argv)
{

Vector3d a1, a2, a3;
a1 << 3,0,0;
a2 << 0.5, 2, 0;
a3<< 0.3, 0.2, 1.5;
Matrix3d A; 
A<< 3,0,0,
    0.5,2,0,
    0.3,0.2,1.5;

// triple product
double tri = a1.dot(a2.cross(a3));

//determinant

double det = A.determinant();

std::cout << "The triple product of a1, a2 and a3 is "<< tri <<std::endl;
std::cout << "The determinant of A is "<< det <<std::endl;
 

return 0;
}