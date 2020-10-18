#ifndef _STOKESSVECTOR_H_
#define _STOKESVECTOR_H_
#include <complex>
#include <iostream>
typedef std::complex<double> Complex;
class StokesVector {

 public:

  enum Type {Horizontal,Vertical,Plus45, Minus45,Right,Left,Unpolarized};

  // Construct a zero vector:
  inline StokesVector();

  // Construct a type from a predefined type
  inline StokesVector(Type type);

  // Construct on two complex numbers:
  inline StokesVector (const double &x0, const double & x1,const double &x2, const double & x3);

  // Compute the magnitude square (=intensity) :
  inline double magsq() const;

  // Access to individual elements:
  inline double & operator () (unsigned int i);
  inline const double & operator () (unsigned int i) const;

 private:

  double x0,x1,x2,x3;

};

inline std::ostream & operator << (std::ostream & o, const StokesVector & v);
inline StokesVector operator* (const StokesVector & v,        const double &c);
inline StokesVector operator* (const double & c,       const StokesVector & v);
#include "JONESCALC/StokesVector.icc"
#endif
