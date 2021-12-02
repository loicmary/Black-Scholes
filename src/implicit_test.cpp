#include "../include/implicit.h"
#include "../include/call.h"
#include "../include/put.h"
#include <iostream>
#include <fstream>
#include <math.h>

/**
 *Fichier de test des fonctionnalitees de base de la classe Implicit
 */
int main()
{
  Put c(1, 300, 100, 0.1);
  Implicit imp(1000, 1000,0.1, c);
  Col_Vector init = imp.get_init_cond();
  Col_Vector price = imp.step_forward(init);
  int i = 0;
  
  while(!imp.is_finished())
    {
      price = imp.step_forward(price);
      i++;
      //std::cout << i << std::endl;
    }

  price = imp.ctilde_to_C(price, c.get_T() * 0.5 * pow(imp.get_sigma(),2));
  std::cout << price << std::endl;

  std::ofstream myfile;
  myfile.open ("result_reduce.txt");
  myfile << price;
  myfile.close();

  return 0;
}
