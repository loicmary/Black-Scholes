#ifndef DIFF_FINIES_H
#define DIFF_FINIES_H

#include "../include/col_vector.h"
#include "../include/payoff.h"

/**
 *Classe representant les methodes aux differences finies pour l'equation de black scholes
 */
class Diff_finies {
 protected:
  /** Nombre d'intervalles de discretisation de [0,S]*/
  int Ns_;
  /** Nombre d'intervalles de discretisation de [0,T]*/
  int Nt_;
  /** Volatilite de l'actif sous jacent */
  double sigma_;
  /** Option en vigueur */
  const Payoff& p_;
  /** indicateur interne du nombre d'etape calculee */
  int step_;

 public:
  Diff_finies(int Ns, int Nt, double sigma, const Payoff &p);

 public:
  int get_Ns() const { return Ns_; };
  int get_Nt() const { return Nt_; };
  double get_sigma() const { return sigma_; };
  int get_step() const { return step_; };
  const Payoff & get_payoff() const { return p_; };

 public:
  virtual Col_Vector get_init_cond() const =0;
  virtual Col_Vector step_forward(const Col_Vector &C)=0;
  bool is_finished() const;
  
};

#endif
