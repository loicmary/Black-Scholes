#include <iostream>
#include "../include/tri_diag_matrix.h"
#include "../include/col_vector.h"

/**
 *Fichier de test des fonctionnalitees de base de la classe Tri_Diag_Matrix.
 */
int main()
{
	Col_Vector b(3);
	b[0]=1;
	b[1]=2;
	b[2]=3;
	Col_Vector a(2);
	a[0]=0;
	a[1]=0;
	Col_Vector c(2);
	c[0]=4;
	c[1]=5;
	Tri_Diag_Matrix A(3,a,b,c);
	std::cout<<"A :"<<std::endl;
	std::cout<<A<<std::endl;

	std::cout<<"a :"<<std::endl;
	std::cout<<A.get_a()<<std::endl;
	std::cout<<"b :"<<std::endl;
	std::cout<<A.get_b()<<std::endl;
	std::cout<<"c :"<<std::endl;
	std::cout<<A.get_c()<<std::endl;
	
	return 0;
}
