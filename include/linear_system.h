#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

#include "tri_diag_matrix.h"
#include "col_vector.h"

/**
 *Classe represantant un systeme lineaire tridiagonale AX = B
 */
class Linear_System {
  /** Nombre d'inconnues du systeme */
  int nb_inconnue_;
  /** Matrice tridiagonale du systeme*/
  Tri_Diag_Matrix A_;
  /** vecteur colonne a droite dans le systeme*/
  Col_Vector B_;

public:
  Linear_System(int nb_inconnue,  Tri_Diag_Matrix &A,  Col_Vector &B);
  Linear_System(const Linear_System &m);
  
public:
  int get_nb_inconnue() const { return nb_inconnue_;}
  Tri_Diag_Matrix get_A() const {return A_;}
  Col_Vector get_B() const {return B_;}
	

public:
  Col_Vector resolution_system_algo_thomas();





};



#endif
