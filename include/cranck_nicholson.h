#ifndef CRANCK_NICHOLSON_H
#define CRANCK_NICHOLSON_H

#include "../include/payoff.h"
#include "../include/col_vector.h"
#include "../include/diff_finies.h"

/**
 *Classe represantant un schema de Cranck-Nicholson pour l'equation complete de black-scholes
 */
class Cranck_Nicholson : public Diff_finies
{
  
 public:
  Cranck_Nicholson(int Ns, int Nt, double sigma, const Payoff &p);

 public:
  Col_Vector get_init_cond() const;
  Col_Vector step_forward(const Col_Vector &C);
};


#endif
