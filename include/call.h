#ifndef CALL_H
#define CALL_H

#include "payoff.h"

/**
 * Classe qui gere les Call
 */
class Call : public Payoff
{

public:
  Call(int T,int L,int K,double r);
  Call(const Call &p);

 public:
  double get_C_T_s(double s) const;
  double get_C_t_0(double t) const;
  double get_C_t_L(double t) const;
};




#endif
