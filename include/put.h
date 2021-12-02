#ifndef PUT_H
#define PUT_H

#include "payoff.h"

/**
 * Classe represantant un put.
 */
class Put : public Payoff
{

public:
  Put(int T,int L,int K,double r);
  Put(const Put &p);

 public:
  double get_C_T_s(double s) const;
  double get_C_t_0(double t) const;
  double get_C_t_L(double t) const;
};




#endif
