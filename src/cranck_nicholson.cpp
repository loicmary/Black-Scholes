#include "../include/cranck_nicholson.h"
#include "../include/diff_finies.h"
#include "../include/col_vector.h"
#include "../include/payoff.h"
#include "../include/tri_diag_matrix.h"
#include "../include/linear_system.h"
#include <iostream>
#include <math.h>

/**
 *Constructeur de la classe Cranck_Nicholson
 *@param Ns (int): Nombre d'intervalles de discretisation de [0,S]
 *@param Nt (int): Nombre d'intervalles de discretisation de [0,T]
 *@param sigma (double): volatilité de l'actif sous jacent
 *@param p (const Payoff& p): Option en vigueur
 */
Cranck_Nicholson::Cranck_Nicholson(int Ns, int Nt,double sigma,const Payoff &p): Diff_finies(Ns,Nt,sigma,p)
{
}

/**
 *Getter du vecteur des conditions initiales relatives au Payoff p_ et de la discretisation en vigueur
 */
Col_Vector Cranck_Nicholson::get_init_cond() const
{
  int Ns = get_Ns();
  Col_Vector vect(Ns + 1);
  const Payoff &p = get_payoff();
  int L = p.get_L();
  double deltaS = (double)L/(double)Ns;
  for(int i = 0; i <= Ns; i++)
    {
      vect[i] = p.get_C_T_s(i * deltaS);
    }
  return vect;
}

/**
 *Fonction renvoyant l'etape suivante dans le calcul du schema de cranck-nicholson et mettant a jour l'indicateur de l'etape de la methode.
 *@param (const Col_Vector &) : Vecteur des valeurs calculée par l'etape precedent du schema
 */
Col_Vector Cranck_Nicholson::step_forward(const Col_Vector &C)
{
  //getters
  int Ns = get_Ns();
  int Nt = get_Nt();
  double sigma = get_sigma();
  const Payoff &p = get_payoff();
  int L = p.get_L();
  int T = p.get_T();
  double r = p.get_r();
  double deltaS = (double)L/(double)Ns;
  double deltaT = (double)T/(double)Nt;

  /*std::cout << "Resume getters" << std::endl;
  std::cout << "Ns :" << Ns << std::endl;
  std::cout << "Nt :" << Nt << std::endl;
  std::cout << "sigma :" << sigma << std::endl;
  std::cout << "L :" << L << std::endl;
  std::cout << "T :" << T << std::endl;
  std::cout << "deltaS :" << deltaS << std::endl;
  std::cout << "deltaT :" << deltaT << std::endl;*/

  //Calcul des constantes
  Col_Vector a(Ns-1);
  Col_Vector b(Ns-1);
  Col_Vector c(Ns-1);

  for(int n = 0; n < Ns-1 ; n++)
    {
      a[n] = 0.5 * pow(sigma, 2) * pow((n+1) * deltaS,2);
    }
  
  for(int n = 0; n < Ns-1 ; n++)
    {
      b[n] = r * (n+1) * deltaS;
    }
  for(int n = 0; n < Ns-1 ; n++)
    {
      c[n] = -r;
    }  

  double mu1 = deltaT/(pow(deltaS, 2));
  double mu2 = deltaT/deltaS;
  Col_Vector alpha(Ns - 1);
  Col_Vector beta(Ns - 1);
  Col_Vector gamma(Ns - 1);
  
  for(int n=0; n < Ns - 1; n++)
    {
      beta[n] = mu1 * a[n] - 0.5 * deltaT * c[n];
    }

  for(int n=0; n < Ns - 1; n++)
    {
      alpha[n] = 0.25 * mu2 * b[n] - 0.5 * mu1 * a[n];
    }
  
  for(int n=0; n < Ns - 1; n++)
    {
      gamma[n] = -0.25 * mu2 * b[n] - 0.5 * mu1 * a[n];
    }

  /*    std::cout << "Resume cst" << std::endl;
  std::cout << "a :" << std::endl << a;
  std::cout << "b :" << std::endl << b;
  std::cout << "c :" << std::endl << c;
  std::cout << "mu1 :" << mu1 << std::endl;
  std::cout << "mu2 :" << mu2 << std::endl;
  std::cout << "alpha :" << std::endl << alpha;
  std::cout << "beta :" << std::endl << beta;
  std::cout << "gamma :" << std::endl << gamma;*/

  //calcul du systï¿½me membre de gauche
  Col_Vector sousDiagL(Ns - 2);
  Col_Vector surDiagL(Ns - 2);
  Col_Vector diagL(Ns - 1);
  
   for(int n=0; n < Ns - 2; n++)
    {
      sousDiagL[n] = alpha[n+1];
    }

   for(int n=0; n < Ns - 1; n++)
    {
      diagL[n] = 1 + beta[n];
    }
  
   for(int n=0; n < Ns - 2; n++)
    {
      surDiagL[n] = gamma[n];
    }

  Tri_Diag_Matrix mL(Ns - 1, sousDiagL, diagL, surDiagL);
  Col_Vector vectL(Ns - 1);
  vectL[0] = alpha[0] * p.get_C_t_0(T - (get_step() + 1) * deltaT);
  vectL[Ns - 2] = gamma[Ns - 2] * p.get_C_t_L(T - (get_step() + 1) * deltaT);
  
  //calcul du systï¿½me membre de droite
  Col_Vector sousDiagR(Ns - 2);
  Col_Vector surDiagR(Ns - 2);
  Col_Vector diagR(Ns - 1);
  
  for(int n=0; n < Ns - 2; n++)
    {
      sousDiagR[n] = -alpha[n+1];
    }

   for(int n=0; n < Ns - 1; n++)
    {
      diagR[n] = 1 - beta[n];
    }
  
  for(int n=0; n < Ns - 2; n++)
    {
      surDiagR[n] = -gamma[n];
    }

  Tri_Diag_Matrix mR(Ns - 1, sousDiagR, diagR, surDiagR);
   
  Col_Vector vectR(Ns - 1);  
  vectR[0] = -alpha[0] * C[0];
  vectR[Ns - 2] = -gamma[Ns - 2] * C[Ns - 1];

  Col_Vector c_reduce(Ns - 1);

  for(int n=0; n < Ns - 1; n++)
    {
      c_reduce[n] = C[n+1];
    }
  Col_Vector mbrR(Ns - 1);
  mbrR =(mR * c_reduce) + (vectR - vectL);

  //Systeme et resolution
  Linear_System sys(Ns - 1, mL, mbrR);
  Col_Vector res = sys.resolution_system_algo_thomas();

  Col_Vector c_next(Ns + 1);
  for(int n=0; n < Ns - 1; n++)
    {
      c_next[n+1] = res[n];
    }
  c_next[0] = p.get_C_t_0(T - (get_step() + 1) * deltaT);
  c_next[Ns] = p.get_C_t_L(T - (get_step() + 1) * deltaT);
  step_ += 1;
  return c_next;
}
