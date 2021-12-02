#include "../include/payoff.h"

/**
 *Constructeur de la classe Payoff.
 *@param T (integer): Temps de maturite de l'option
 *@param L (integer): Prix maximum de l'actif sous jacent
 *@param K (integer): Strike de l'actif
 *@param r (double): taux d'interet en vigueur
 */
Payoff::Payoff(int T,int L,int K,double r):T_(T),L_(L),K_(K),r_(r)
{
}

/**
 *Constructeur de copie de la classe Payoff.
 *@param p (const Call&) : call a copier
 */
Payoff::Payoff(const Payoff &p):T_(p.get_T()),L_(p.get_L()),K_(p.get_K()),r_(p.get_r())
{
}

/**
 *Fonction max entre 2 entiers
 *@param K (integer): 1er entier a comparer
 ù@param s (integer): 2em entier a comparer
 */
int Payoff::max(int K, int s) const{
	if(K>=s)
		return K;
	else
		return s;
}
