#include "../include/call.h"
#include <iostream>
/**
 * Fichier de test des fonctions basiques de la classe call
 */
int main()
{
  Call c(1, 300, 100, 0.1);
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
