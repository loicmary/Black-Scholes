#include "../include/put.h"
#include "../include/col_vector.h"
#include <math.h>

/**
 *Constructeur de la classe ut.
 *@param T (integer): Temps de maturite de l'option
 *@param L (integer): Prix maximum de l'actif sous jacent
 *@param K (integer): Strike de l'actif
 *@param r (double): taux d'interet en vigueur
 */
Put::Put(int T, int L, int K, double r): Payoff(T,L,K,r)
{
  
}

/**
 *Constructeur de copie de la classe Put.
 *@param p (const Call&) : put a copier
 */
Put::Put(const Put &p): Payoff(p)
{
}

/**
 *Getter de la condition a maturite du prix de l'option (lorsque t = T).
 *Si s < 0 alors le calcul se fait pour s = 0 et si s > L le calcul se fait pour s = L.
 *@param s (double): prix de l'actif sous jacent a l'instant T
 */
double Put::get_C_T_s(double s) const {
  int L = get_L();
  int K = get_K();
  
  if(s < 0)
    {
      s = 0;
    }
  else if(s > L)
    {
      s = L;
    }
    

  return max(0, K - s);
}

/**
 *Getter de la condition au bord du prix de l'option (lorsque s = L)
 *Si t < 0 alors le calcul se fait pour t = 0 et si t > T le calcul se fait pour t = T.
 *@param t (double) : temps a laquel est evalue le prix de l'option
 */
double Put::get_C_t_L(double t) const
{
  int T = get_T();
  
  if(t < 0)
    {
      t = 0;
    }
  else if(t > T)
    {
      t = T;
    }
  
  return 0;
}

/**
 *Getter de la condition au bord du prix de l'option (lorsque s = 0).
 *Si t < 0 alors le calcul se fait pour t = 0 et si t > T le calcul se fait pour t = T.
 *@param t (double) : temps a laquel est evalue le prix de l'option
 */
double Put::get_C_t_0(double t) const
{
  int T = get_T();
  int K = get_K();
  double r = get_r();
  
  if(t < 0)
    {
      t = 0;
    }
  else if(t > T)
    {
      t = T;
    }
  
  return K * exp(-r * (T - t));
}
