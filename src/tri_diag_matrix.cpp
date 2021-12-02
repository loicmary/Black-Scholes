#include "../include/tri_diag_matrix.h"
#include <iostream>


/**
 *Constructeur d'une matrice tridiagonale carree de taille nl x nl.
 *Throw "bad vector shapes" si les vecteurs en arguments ne sont pas de bonne dimensions.
 *@param nl (integer) : nombre de lignes.
 *@param a (Col_Vector) : La sous diagonale a
 *@param b (Col_vector) : La diagonale b
 *@param c (Col_Vector) : La sur diagonale c
 */
Tri_Diag_Matrix::Tri_Diag_Matrix(int nl, const Col_Vector& a, const Col_Vector& b, const Col_Vector& c) : BMatrix(nl,nl)
{
  //Verification des dimensions des vecteurs
  if(a.get_length() != nl - 1 || b.get_length() != nl || c.get_length() != nl - 1)
    {
      throw "Bad vector shapes";
    }
  
  for(int i=0; i < get_nl(); i++)
  {
    //Diagonale b
    data_[i * get_nc() + i] = b[i];

    if(i < get_nl() - 1) //Evite index out of bound dans le cas i = get_nl() - 1
      {
	//SurDiagonale c
	data_[i * get_nc() + (i+1)] = c[i];

	//SousDiagonale a
	data_[(i+1) * get_nc() + i] = a[i];
      }
    
  }
}

/**
 *Constructeur de copie des matrices  tridiagonales.
 * Throw "Bad shaped" si la matrice a copier na pas les memes dimensions.
 *@param m (Tri_Diag_Matrix) : La matrice a copier
 */
Tri_Diag_Matrix::Tri_Diag_Matrix(const Tri_Diag_Matrix &m): BMatrix(m.get_nl(),m.get_nl())
{
  Col_Vector a(m.get_a());
  Col_Vector b(m.get_b());
  Col_Vector c(m.get_c());

  int nl = get_nl();
    //Verification des dimensions des vecteurs
  if(a.get_length() != nl - 1 || b.get_length() != nl || c.get_length() != nl - 1)
    {
      throw "Bad shapes";
    }
  
  for(int i=0; i < get_nl(); i++)
  {
    //Diagonale b
    data_[i * get_nc() + i] = b[i];

    if(i < get_nl() - 1) //Evite index out of bound dans le cas i = get_nl() - 1
      {
	//SurDiagonale c
	data_[i * get_nc() + (i+1)] = c[i];

	//SousDiagonale a
	data_[(i+1) * get_nc() + i] = a[i];
      }
    
  }
}

/**
 * Renvois la sous diagonale.
 */
Col_Vector Tri_Diag_Matrix::get_a() const
{
  Col_Vector res(get_nl() - 1);
  for(int i=0; i < get_nl() - 1; i++)
    {
      res[i] = data_[(i+1) * get_nc() + i];
    }
  return res;
}

/**
 * Renvois la diagonale.
 */
Col_Vector Tri_Diag_Matrix::get_b() const
{
  Col_Vector res(get_nl());
  for(int i=0; i < get_nl(); i++)
    {
      res[i] = data_[i * get_nc() + i];
    }
  return res;
}

/**
 * Renvois la sur-diagonale.
 */
Col_Vector Tri_Diag_Matrix::get_c() const
{
  Col_Vector res(get_nl() - 1);
  for(int i=0; i < get_nl() - 1; i++)
    {
      res[i] = data_[i * get_nc() + (i+1)];
    }
  return res;
}
