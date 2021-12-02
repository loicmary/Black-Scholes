#include "../include/linear_system.h"
#include "../include/tri_diag_matrix.h"
#include "../include/col_vector.h"
#include <iostream>

/**
 *Constructeur des systeme lineaire AX = B.
 *@param nb_inconnue (integer): nombre d'inconnues du systeme.
 *@param A (Tri_Diag_Matrix) : la matrice des coefficients.
 *@param B (Col_Vector) : le vecteur colonne
 */
Linear_System::Linear_System(int nb_inconnue,  Tri_Diag_Matrix &A,  Col_Vector &B):nb_inconnue_(nb_inconnue), A_(A), B_(B)
{

}


Linear_System::Linear_System(const Linear_System &m):nb_inconnue_(m.get_nb_inconnue()), A_(m.get_A()), B_(m.get_B())
{

}


/**
 * Resolution d'un système tridiagonale rapide par l'algorithme de Thomas
 */
Col_Vector Linear_System::resolution_system_algo_thomas(){
	Col_Vector a=A_.get_a();
	Col_Vector b=A_.get_b();
	Col_Vector c=A_.get_c();

	Col_Vector gamma(nb_inconnue_-1);
	gamma[0]=c[0]/b[0];
	for(int i=1;i<nb_inconnue_-1;i++){
		gamma[i]=c[i]/(b[i]-a[i-1]*gamma[i-1]);
	}
	Col_Vector beta(nb_inconnue_);
	beta[0]=B_[0]/b[0];
	for(int j=1;j<nb_inconnue_;j++){
		beta[j]=(B_[j]-a[j-1]*beta[j-1])/(b[j]-a[j-1]*gamma[j-1]);
	}
	Col_Vector X(nb_inconnue_);
	X[nb_inconnue_-1]=beta[nb_inconnue_-1];
	for (int k=nb_inconnue_-2;k>=0;k--){
		X[k]=beta[k]-gamma[k]*X[k+1];
	}
	return X;


}
