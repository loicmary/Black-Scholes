#include "../include/implicit.h"
#include "../include/col_vector.h"
#include "../include/tri_diag_matrix.h"
#include "../include/linear_system.h"
#include <math.h>
#include <iostream>

/**
 *Constructeur de la classe Implicit
 *@param Ns (int): Nombre d'intervalles de discretisation de [0,S]
 *@param Nt (int): Nombre d'intervalles de discretisation de [0,T]
 *@param sigma (double): volatilite de l'actif sous jacent
 *@param p (const Payoff& p): Option en vigueur
 */
Implicit::Implicit(int Ns, int Nt, double sigma, const Payoff &p): Diff_finies(Ns, Nt, sigma, p)
{
}

/**
 *Getter du vecteur des conditions initiales relatives au Payoff p_ et de la discretisation en vigueur
 */
Col_Vector Implicit::get_init_cond() const
{
  int Ns = get_Ns();
  Col_Vector res(Ns + 1);
  const Payoff& p = get_payoff();
  double r = p.get_r();
  double sigma = get_sigma();
  int L = p.get_L();
  int K = p.get_K();
  double S_moins = -5;
  double deltaStilde = (log((double)L/(double)K) - S_moins)/(double)Ns;
  double k = (2*r)/pow(sigma,2);
  double alpha_const = -0.5*(k-1);
  
  for(int n=0; n < Ns + 1; n++)
    {
      double Stilde = S_moins + n * deltaStilde;
      res[n] = (double)1/(double)K * exp(-alpha_const*Stilde) * p.get_C_T_s(K*exp(Stilde));
    }

  return res;
}

/**
 *Fonction renvoyant l'etape suivante dans le calcul du schema de cranck-nicholson et mettant a jour l'indicateur de l'etape de la methode.
 *@param (const Col_Vector &) : Vecteur des valeurs calcul�e par l'etape precedent du schema
 */
Col_Vector Implicit::step_forward(const Col_Vector &C)
{
    //getters
  int Ns = get_Ns();
  int Nt = get_Nt();
  double sigma = get_sigma();
  const Payoff &p = get_payoff();
  int L = p.get_L();
  int T = p.get_T();
  int K = p.get_K();
  double r = p.get_r();
  double S_moins = -5;
  double deltaStilde = (log((double)L/(double)K) - S_moins)/(double)Ns;
  double deltaTtilde = (pow(sigma,2)*T*0.5)/Nt;
  double k = (2*r)/pow(sigma,2);
  double alpha_const = -0.5*(k-1);
  double beta_const = -0.25*pow(k+1,2);
  
  //Calcul des constantes
  double lambda = deltaTtilde / pow(deltaStilde, 2);

  //Calcul membre de gauche
  Col_Vector sousDiag(Ns - 2);
  Col_Vector diag(Ns - 1);

    for(int n=0; n < Ns - 2; n++)
    {
      sousDiag[n] = -lambda;
    }
  for(int n=0; n < Ns - 1; n++)
    {
      diag[n] = 1 + 2*lambda;
    }

  Tri_Diag_Matrix mL(Ns-1, sousDiag, diag, sousDiag);
  
  Col_Vector vectL(Ns-1);
  double tTildej = (get_step() + 1)*deltaTtilde;
  double C_J_0 = ((double) 1/ (double)K) * exp(-alpha_const*S_moins - beta_const*tTildej) * p.get_C_t_0(T - (2 * tTildej)/(pow(sigma,2)));
  double C_J_Ns = ((double) 1 / (double) K)* exp(-alpha_const*log((double) L/(double)K) - beta_const*tTildej)*p.get_C_t_L(T - (2 * tTildej)/(pow(sigma,2)));
  vectL[0] = -lambda * C_J_0;
  vectL[Ns-2] = -lambda * C_J_Ns;
  
   //Calcul du membre de droite
  Col_Vector c_reduce(Ns-1);
  for(int n=0; n < Ns - 1;n++)
    {
      c_reduce[n] = C[n+1];
    }

  Col_Vector mbrR(Ns-1);
  mbrR = c_reduce  - vectL;
  
  Linear_System sys(Ns - 1, mL,mbrR);
  Col_Vector res = sys.resolution_system_algo_thomas();
  Col_Vector c_next(Ns+1);
  for(int n=0; n < Ns - 1; n++)
    {
      c_next[n+1] = res[n];
    }
  c_next[0] = C_J_0;
  c_next[Ns] = C_J_Ns;
  step_++;

  return c_next;
}


/**
 *Fonction renvoyant le vecteur correspondant aux valeur de C etant donner le vecteur Ctilde et tTilde
 *@param c_tilde (const Col_Vector &) : Vecteur des valeur Ctilde
 *@param tTilde (double) : temps du calcul du vecteur c_tilde
 */
Col_Vector Implicit::ctilde_to_C(const Col_Vector &c_tilde, double tTilde) const
{
  int Ns = get_Ns();
  double sigma = get_sigma();
  const Payoff &p = get_payoff();
  int L = p.get_L();
  int K = p.get_K();
  double r = p.get_r();
  double S_moins = -5;
  double deltaStilde = (log((double)L/(double)K) - S_moins)/(double)Ns;
  double k = (2*r)/pow(sigma,2);
  double alpha_const = -0.5*(k-1);
  double beta_const = -0.25*pow(k+1,2);
  
  if(c_tilde.get_length() != Ns + 1)
    {
      throw "Wrong size vector";
    }

  Col_Vector c_transforme(Ns + 1);
  for(int n=0; n < Ns + 1; n++)
    {
      double Stilde = S_moins + n * deltaStilde;
      c_transforme[n] = K * exp(alpha_const * Stilde + beta_const * tTilde) * c_tilde[n];
    }

  return c_transforme;
}
