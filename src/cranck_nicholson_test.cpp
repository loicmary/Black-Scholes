#include "../include/cranck_nicholson.h"
#include "../include/call.h"
#include "../include/put.h"
#include <iostream>
#include <fstream>
#include <math.h>

int main()
{
  Put c(1, 300, 100, 0.1);
  Cranck_Nicholson crk(1000, 1000,0.1, c);
  Col_Vector init = crk.get_init_cond();
  Col_Vector price = init;
  int i = 0;

  price = crk.step_forward(price);

   while(!crk.is_finished())
    {
      //std::cout << i << std::endl;
      i++;
      price = crk.step_forward(price);

    }
  std::cout << "Resultat final" << std::endl;
  
  std::cout << price << std::endl;

  //std::ofstream myfile;
  //myfile.open ("result.txt");
  //myfile << price;
  //myfile.close();
  return 0;
}
