#ifndef IMPLICIT_H
#define IMPLICIT_H

#include "../include/diff_finies.h"
#include "../include/payoff.h"
#include "../include/col_vector.h"

/**
 *Classe represantant un schema aux differences finies implicite pour l'equation reduite de black-scholes
 */
class Implicit : public Diff_finies
{
 public:
  Implicit(int Ns, int Nt, double sigma, const Payoff &p);

 public:
  Col_Vector get_init_cond() const;
  Col_Vector step_forward(const Col_Vector &C);
  Col_Vector ctilde_to_C(const Col_Vector &C, double tTilde) const;
};

#endif
