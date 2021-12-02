#include <iostream>
#include "../include/col_vector.h"

/**
 *Fichier de test des fonctionnalitees de base de la classe Col_Vector
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
	
	std::cout << "Taille a :" << a.get_length() << std::endl;
	b[1] = 4;
	std::cout << b << std::endl;
	a = c;
	std::cout << a << std::endl;

	try
	  {
	    a = b;
	  }
	catch(...)
	  {
	    std::cout << "error catched" << std::endl;
	  }
	
	return 0;
}
