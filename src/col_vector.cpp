#include "../include/col_vector.h"


/**
 *Constructeur des vecteurs colonne Col_Vector de taille length x 1.
 *@param length (interger) : taille du vecteur colonne
 */
Col_Vector::Col_Vector(int length) : BMatrix(length,1){
	length_=length;
}

/**
 *Constructeur de copie des vecteurs colonnes.
 *@param v (Col_Vector) : le vecteur à copier
 */
Col_Vector::Col_Vector(const Col_Vector & v): BMatrix(v.get_length(),1)
{
    length_ = v.get_length();
    data_ = new double[length_];
    if (!data_)
      throw "allocation of memory failed"; //Peut s'enlever je pense vu que déj) fait dans le constructeur de BMatrix

    for (int i = 0; i < v.get_length(); i++)
        data_[i] = v[i];
}

/**
 *Surcharge operateur d'affectation.
 * Throw "bad dimensions" si les tailles ne correspondent pas.
 *@param v (Col_Vector): le vecteur a affecter
 */
Col_Vector &Col_Vector::operator=(const Col_Vector & v)
{
  if(this != &v)
    {
      if(get_nl() != v.get_nl())
	{
	  throw "bad dimensions";
	}
      Col_Vector temp = v;
      for(int i=0; i < v.get_nl(); i++)
	{
	  (*this)[i] = v[i];
	}
    }
  return *this;
}

/**
 *Surcharge operateur d'acces aux elements du vecteur colonne.
 * L'acces se fait pour un indice entre 0 et length - 1.
 * Throw "wrong index" si l'indice est hors des dimensions de la matrice.
 *@param idx (integer) : index de l'acces
 */
double Col_Vector::operator[](int idx) const
{
    if ((idx < 0) || (idx >= length_))
        throw "wrong index";

    return data_[idx];
}

/**
 *Surcharge operateur d'acces constant aux elements du vecteur colonne.
 * L'acces se fait pour un indice entre 0 et length - 1.
 * Throw "wrong index" si l'indice est hors des dimensions de la matrice
 *@param idx (integer) : index de l'acces
 */
double &Col_Vector::operator[](int idx)
{
    if ((idx < 0) || (idx >= length_))
        throw "wrong index";

    return data_[idx];
}

/**
 * Operateur d'addition interne pour les Col_Vector.
 * Throw "size mismatched" si le vecteur a additionner n'est pas de la meme dimension que le vecteur courant.
 *@param m (const Col_Vector&) : vecteur a additionner
 */
Col_Vector & Col_Vector::operator+=(const Col_Vector & m)
{
    if (!same_size(m))
        throw "size mismatched";

    for (int i = 0; i < get_nl(); i++)
        for (int j = 0; j < get_nc(); j++)
            operator()(i, j) += m(i, j);

    return *this;
}

/**
 * Operateur de soustraction interne pour les Col_Vector.
 * Throw "size mismatched" si le vecteur a soustraire n'est pas de la meme dimension que le vecteur courant.
 *@param m (const Col_Vector&) : vecteur a soustraire
 */
Col_Vector & Col_Vector::operator-=(const Col_Vector & m)
{
    if (!same_size(m))
        throw "size mismatched";

    for (int i = 0; i < get_nl(); i++)
        for (int j = 0; j < get_nc(); j++)
            operator()(i, j) -= m(i, j);

    return *this;
}

/**
 *Operateur externe de multiplication de BMatrix a gauche par un Col_Vector a droite.
 *Throw "size mismatched" si les tailles ne sont pas compatible à la multiplication matricielle.
 *@param m1 (const BMatrix &) : La matrice a gauche
 *@param v (const Col_Vector&) : Le vecteur a gauche
 */
Col_Vector operator*(const BMatrix & m1, const Col_Vector & v)
{
    if (m1.get_nc() != v.get_nl())
        throw "size mismatched";

    Col_Vector m(m1.get_nl());

    for (int i = 0; i < m.get_nl(); i++)
    {
        for (int j = 0; j < m.get_nc(); j++)
        {
            double val = 0;
            for (int k = 0; k < m1.get_nc(); k++)
                val += m1(i, k) * v(k, j);
            m(i, j) = val;
        }
    }

    return m;
}

/**
 *Operateur externe d'addition de Col_Vector.
 *Throw "size mismatched" si les tailles des vecteurs ne sont pas identiques.
 *@param v1 (const Col_Vector&) : Le vecteur a gauche
 *@param v2 (const Col_Vector&) : Le vecteur a droite
 */
Col_Vector operator+(const Col_Vector & v1, const Col_Vector & v2)
{
    if (!v1.same_size(v2))
        throw "size mismatched";

    Col_Vector v = v1;

    return v += v2;
}

/**
 *Operateur externe de soustraction de Col_Vector.
 *Throw "size mismatched" si les tailles des vecteurs ne sont pas identiques.
 *@param v1 (const Col_Vector&) : Le vecteur a gauche
 *@param v2 (const Col_Vector&) : Le vecteur a droite
 */
Col_Vector operator-(const Col_Vector & v1, const Col_Vector & v2)
{
    if (!v1.same_size(v2))
        throw "size mismatched";

    Col_Vector v = v1;

    return v -= v2;
}
