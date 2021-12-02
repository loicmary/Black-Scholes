#ifndef COL_VECTOR_H
#define COL_VECTOR_H
#include "bmatrix.h"

/**
 *Classe representant un vecteur colonne
 */
class Col_Vector : public BMatrix
{
  /** Taille du vecteur */
  int length_;

public:
  Col_Vector(int length);
  Col_Vector(const Col_Vector &m);

public: //getters
  int get_length() const { return length_;}
  double operator[](int idx) const;

public:
  double & operator[](int idx);
  Col_Vector & operator=(const Col_Vector & v);
  Col_Vector & operator+=(const Col_Vector & m);
  Col_Vector & operator-=(const Col_Vector & m);

  friend Col_Vector operator*(const BMatrix & m1, const Col_Vector & m2);
  friend Col_Vector operator+(const Col_Vector & v1, const Col_Vector & v2);
  friend Col_Vector operator-(const Col_Vector & v1, const Col_Vector & v2);	
};

#endif
