#include "../include/bmatrix.h"
#include "../include/col_vector.h"
#include <stdio.h>

/**
 * Constructeur des BMatrix.
 * Initialise la matrice nulle de taille nl x nc.
 * Throw "invalid size" si la taille est negative ou nulle.
 * Throw "not enough memory" si l'allocation memoire ne s'est pas faite.
 * @param nl (integer) : nombre de lignes
 * @param nc (integer) : nombre de colonnes
 */
BMatrix::BMatrix(int nl, int nc)                                                        
{                                                                                       
    if ((nl <= 0) || (nc <= 0))                                                         
        throw "invalid size";                                                           
                                                                                        
    nl_ = nl;                                                                           
    nc_ = nc;
    data_ = new double[nl * nc];
    if (!data_)
      {
        throw "not enough memory";
      }
    for(int i=0; i < nl * nc; i++)
    {
      data_[i] = 0;
    }
}

/**
 * Destructeur des Constructeur des BMatrix.
 * Libere la memoire allouee de la BMatrix.
 */
BMatrix::~BMatrix()
{
    delete [] data_;
}

/**
 *Surcharge de l'operateur de flux.
 * Affichage de la matrice lignes par lignes.
 */
std::ostream & operator<<(std::ostream & st, const BMatrix & m)                         
{                                                                                       
    for (int i = 0; i < m.get_nl(); i++)                                                
    {                                                                                   
        for (int j = 0; j < m.get_nc(); j++)                                            
        {                                                                               
            st << m(i,j);                                                              
            if (j < (m.get_nc() - 1))                                                   
                st << " ";                                                              
        }                                                                               
        st << "\n";                                                                     
    }                                                                                   
                                                                                        
    return st;                                                                          
}

/**
 *Operateur d'acces constant aux elements de la matrice.
 *L'indexation se fait de 0 a nl - 1 pour les lignes et de 0 a nc - 1 pour les colonnes.
 *Throw "wrong index" si l ou c est hors des dimensions.
 *@param l (integer) : ligne d'acces
 *@param c (integer) : colonne d'acces
 */
double BMatrix::operator()(int l, int c) const
{
    if ((l < 0) || (l >= get_nl()) || (c < 0) || (c >= get_nc()))
        throw "wrong index";

    return data_[l * get_nc() + c];
}

/**
 *Operateur d'acces aux elements de la matrice.
 *L'indexation se fait de 0 a nl - 1 pour les lignes et de 0 a nc - 1 pour les colonnes.
 *Throw "wrong index" si l ou c est hors des dimensions.
 *@param l (integer) : ligne d'acces
 *@param c (integer) : colonne d'acces
 */
double & BMatrix::operator()(int l, int c)
{
    if ((l < 0) || (l >= get_nl()) || (c < 0) || (c >= get_nc()))
        throw "wrong index";

    return data_[l * get_nc() + c];
}

/**
 * Renvois un boolean determinant si la matrice m est de meme dimension que la matrice courante.
 *@param m (BMatrix) : la matrice a comparee 
 */
bool BMatrix::same_size(const BMatrix & m) const
{
    return (get_nl() == m.get_nl()) && (get_nc() == m.get_nc());
}

/**
 * Surcharge de l'operateur d'affectation des matrices.
 *@param m (BMatrix) : la matrice a affectee
 */
BMatrix & BMatrix::operator=(const BMatrix & m)
{
    if (this != &m)
    {
        BMatrix tmp = m;
        double *d = tmp.data_;
        tmp.data_ = data_;
        data_ = d;
        nl_ = m.get_nl();
        nc_ = m.get_nc();
    }

    return *this;
}

/**
 * Surcharge de l'operateur d'addition des matrices.
 * Throw "size mismatched" si les tailles ne correspondent pas.
 *@param m (BMatrix) : la matrice a ajoutee
 */
BMatrix & BMatrix::operator+=(const BMatrix & m)
{
    if (!same_size(m))
        throw "size mismatched";

    for (int i = 0; i < get_nl(); i++)
        for (int j = 0; j < get_nc(); j++)
            operator()(i, j) += m(i, j);

    return *this;
}

/**
 * Surcharge de l'operateur de soustraction des matrices.
 * Throw "size mismatched" si les tailles ne correspondent pas.
 *@param m (BMatrix) : la matrice a soustraire
 */
BMatrix & BMatrix::operator-=(const BMatrix & m)
{
    if (!same_size(m))
        throw "size mismatched";

    for (int i = 0; i < get_nl(); i++)
        for (int j = 0; j < get_nc(); j++)
            operator()(i, j) -= m(i, j);

    return *this;
}

/**
 * Surcharge de l'operateur exterieur d'addition des matrices.
 * Renvois la matrice resultante de l'addition.
 * Throw "size mismatched" si les tailles ne correspondent pas.
 *@param m1 (BMatrix) : la 1ere matrice a additionner
 *@param m2 (BMatrix) : la 2em matrice a additionner
 */
BMatrix operator+(const BMatrix & m1, const BMatrix & m2)
{
    if (!m1.same_size(m2))
        throw "size mismatched";

    BMatrix m = m1;

    return m += m2;
}

/**
 * Surcharge de l'operateur exterieur de soustraction des matrices.
 * Renvois la matrice resultante de la soustraction.
 * Throw "size mismatched" si les tailles ne correspondent pas.
 * @param m1 (BMatrix) : la 1ere matrice a soustraire
 * @param m2 (BMatrix) : la 2em matrice a soustraire
 */
BMatrix operator-(const BMatrix & m1, const BMatrix & m2)
{
    if (!m1.same_size(m2))
        throw "size mismatched";

    BMatrix m = m1;

    return m -= m2;
}

/**
 * Surcharge de l'operateur exterieur de multiplication des matrices.
 * Renvois la matrice resultante de la multiplication.
 * Throw "size mismatched" si les tailles ne correspondent pas.
 * @param m1 (BMatrix) : la matrice a gauche de la multiplication
 * @param m2 (BMatrix) : la matrice a droite de la multiplication
 */
BMatrix operator*(const BMatrix & m1, const BMatrix & m2)
{
    if (m1.get_nc() != m2.get_nl())
        throw "size mismatched";

    BMatrix m(m1.get_nl(), m2.get_nc());

    for (int i = 0; i < m.get_nl(); i++)
    {
        for (int j = 0; j < m.get_nc(); j++)
        {
            double val = 0;
            for (int k = 0; k < m1.get_nc(); k++)
                val += m1(i, k) * m2(k, j);
            m(i, j) = val;
        }
    }

    return m;
}




/**
 * Surcharge de l'operateur exterieur de multiplication d'une matrices par un scalaire.
 * Renvois la matrice resultante de la multiplication.
 * @param val (double) : le scalaire de la mutiplication
 * @param m (BMatrix) : la matrice de la multiplication
 */
BMatrix operator*(double val, const BMatrix & m)
{
    BMatrix res(m.get_nl(), m.get_nc());

    for (int i = 0; i < res.get_nl(); i++)
        for (int j = 0; j < res.get_nc(); j++)
            res(i, j) = m(i, j) * val;

    return res;
}
