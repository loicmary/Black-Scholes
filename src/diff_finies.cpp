#include "../include/diff_finies.h"

/**
 *Constructeur de la classe Diff_finies
 *@param Ns (int): Nombre d'intervalles de discretisation de [0,S]
 *@param Nt (int): Nombre d'intervalles de discretisation de [0,T]
 *@param sigma (double): volatilité de l'actif sous jacent
 *@param p (const Payoff& p): Option en vigueur
 */
Diff_finies::Diff_finies(int Ns, int Nt,double sigma,const Payoff &p): Ns_(Ns), Nt_(Nt),sigma_(sigma), p_(p), step_(0)
{
}

/**
 *Indique si la methode a finis les calculs
 */
bool Diff_finies::is_finished() const
{
  return step_ == get_Nt();
}
