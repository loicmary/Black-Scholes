#ifndef TRI_DIAG_MATRIX_H
#define TRI_DIAG_MATRIX_H

#include "../include/bmatrix.h"
#include "../include/col_vector.h"

/**
 * Classe represantant une matrice tridiagonale
 */
class Tri_Diag_Matrix : public BMatrix
{
public:
  Tri_Diag_Matrix(int nl, const Col_Vector &a,const Col_Vector &b,const Col_Vector &c);
  Tri_Diag_Matrix(const Tri_Diag_Matrix &m);

public:
  Col_Vector get_a() const;
  Col_Vector get_b() const;
  Col_Vector get_c() const;
};

#endif
