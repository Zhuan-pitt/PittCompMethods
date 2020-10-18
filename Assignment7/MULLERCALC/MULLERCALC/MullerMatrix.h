#ifndef _MULLERMATRIX_H_
#define _MULLERMATRIX_H_
#include <complex>
class MullerMatrix {

 public:

  enum Type { Identity, Horizontal,Vertical, Plus45, Minus45, FastHorizontal, FastVertical, FastVerHor};

  // Construct the identity matrix:
  inline MullerMatrix();

  
  // Construct a type from a predefined type
  inline MullerMatrix(Type type);
  
  // Construct on two complex numbers:
  inline MullerMatrix (const double &a00, const double & a01,const double &a02, const double & a03,
  const double &a10, const double & a11,const double &a12, const double & a13,
  const double &a20, const double & a21,const double &a22, const double & a23,
  const double &a30, const double & a31,const double &a32, const double & a33);
  
  // Access to individual elements:
  inline double & operator       () (unsigned int i, unsigned int j);
  inline const double & operator () (unsigned int i, unsigned int j) const;

 private:

  double a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,a23,a30,a31,a32,a33;
  double phi;

};

inline std::ostream & operator << (std::ostream & o, const MullerMatrix & v);
inline MullerMatrix operator* (const MullerMatrix & m1, const MullerMatrix & m2);
inline StokesVector operator* (const MullerMatrix & m, const StokesVector & v);
#include "JONESCALC/MullerMatrix.icc"
#endif
