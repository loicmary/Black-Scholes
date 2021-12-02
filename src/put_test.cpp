#include "../include/put.h"
#include <iostream>

/**
 *Fichier testant les fonctionnalitees de base de la classe Put.
 */
int main()
{
  Put c(1, 300, 100, 0.1);
  std::cout << "t = T s = 200" << std::endl;
  std::cout << c.get_C_T_s(200) << std::endl;
  std::cout << "t = T s = 50" << std::endl;
  std::cout << c.get_C_T_s(50) << std::endl;
  std::cout << "t = 0.5 s = 0" << std::endl;
  std::cout << c.get_C_t_0(0.5) << std::endl;
  std::cout << "t = 0.5 s = L" << std::endl;
  std::cout << c.get_C_t_L(0.5) << std::endl;
  return 0;
}
