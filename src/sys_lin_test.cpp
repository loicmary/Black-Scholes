#include <iostream>
#include "../include/tri_diag_matrix.h"
#include "../include/col_vector.h"
#include "../include/linear_system.h"

/**
 * Fichier de test des fonctionnalitees de base de la classe Linear_System
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
	

	Col_Vector B(3);
	B[0]=1;
	B[1]=-4;
	B[2]=2;
	std::cout<<"B :"<<std::endl;
	std::cout<<B<<std::endl;

	Linear_System s(3,A,B);

	std::cout<<B.get_length()<<std::endl;
	std::cout<<"La solution du systeme est :"<<std::endl;
	std::cout<<s.resolution_system_algo_thomas()<<std::endl;



	return 0;
}
