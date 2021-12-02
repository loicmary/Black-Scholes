#include <iostream>
#include "../include/tri_diag_matrix.h"
#include "../include/col_vector.h"
#include "../include/linear_system.h"
#include "../include/put.h"
#include "../include/call.h"
#include "../include/implicit.h"
#include "../include/cranck_nicholson.h"
#include <fstream>
#include <math.h>

int main()
{
  Put p_cn(1, 300, 100, 0.1);
  Cranck_Nicholson cn_put(1000, 1000,0.1, p_cn);
  Col_Vector init_cn_put = cn_put.get_init_cond();
  Col_Vector price_cn_put = cn_put.step_forward(init_cn_put);

  Put p_impli(1, 300, 100, 0.1);
  Implicit imp_put(1000, 1000,0.1, p_impli);
  Col_Vector init_imp_put = imp_put.get_init_cond();
  Col_Vector price_imp_put = imp_put.step_forward(init_imp_put);

  Call c_impli(1, 300, 100, 0.1);
  Implicit imp_call(1000, 1000,0.1, c_impli);
  Col_Vector init_imp_call = imp_call.get_init_cond();
  Col_Vector price_imp_call = imp_call.step_forward(init_imp_call);
	 
  Call c_cn(1, 300, 100, 0.1);
  Cranck_Nicholson cn_call(1000, 1000,0.1, c_cn);
  Col_Vector init_cn_call = cn_call.get_init_cond();
  Col_Vector price_cn_call = cn_call.step_forward(init_cn_call);
  int i = 0;
  
  while(!cn_call.is_finished())
    {
      price_cn_call = cn_call.step_forward(price_cn_call);
      price_cn_put = cn_put.step_forward(price_cn_put);
      price_imp_call=imp_call.step_forward(price_imp_call);
      price_imp_put=imp_put.step_forward(price_imp_put);
      i++;
      //std::cout << i << std::endl;
    }
    //std::cout<<"la valeur du vecteur C(0,.) est :"<<std::endl;
    //std::cout << price << std::endl;

  price_imp_call = imp_call.ctilde_to_C(price_imp_call, c_impli.get_T() * 0.5 * pow(imp_call.get_sigma(),2));
  price_imp_put = imp_put.ctilde_to_C(price_imp_put, c_impli.get_T() * 0.5 * pow(imp_call.get_sigma(),2));
  std::ofstream myfile;
  myfile.open ("call_cn.txt");
  myfile << price_cn_call;
  myfile.close();

  std::ofstream myfile2;
  myfile2.open ("put_cn.txt");
  myfile2 << price_cn_put;
  myfile2.close();

  std::ofstream myfile3;
  myfile3.open ("call_impli.txt");
  myfile3 << price_imp_call;
  myfile3.close();

  std::ofstream myfile4;
  myfile4.open ("put_impli.txt");
  myfile4 << price_imp_put;
  myfile4.close();

  std::cout<<"Tous les fichiers contenant le vecteur C(0,.) ont été créé et se trouvent dans le dossier bin"<<std::endl;

  return 0;
	
}
