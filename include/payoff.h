#ifndef PAYOFF_H
#define PAYOFF_H

#include "col_vector.h"

/**
 *Classe abstraite represantant un Payoff de maniere generale
 */
class Payoff {
protected:
  /** Temps de matrite T*/
  int T_;
  /** Maximum de la valeur de l'actif sous jacent*/
  int L_;
  /** Strike K de l'option*/
  int K_;
  /** Taux d'interet en vigueur*/
  double r_;
	
public:
  Payoff(int T,int L,int K,double r);
  Payoff(const Payoff &p);



public:
  int get_T() const {return T_;}
  int get_L() const {return L_;}
  int get_K() const {return K_;}
  double get_r() const {return r_;}

  virtual double get_C_T_s(double s) const = 0;
  virtual double get_C_t_0(double t) const = 0;
  virtual double get_C_t_L(double t) const = 0;

public:
  int max(int K,int s) const;

};

#endif
