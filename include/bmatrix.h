#ifndef BMATRIX_H
#define BMATRIX_H

#include <ostream>
/**
 *Classe des matrices de taille quelconque (les elements sont des doubles)
 */
class BMatrix{

protected:
  /** Nombre de lignes */
  int nl_;
  /** Nombre de colonnes */
  int nc_;
  /** Tableau de donnees */
  double *data_;

public:
  BMatrix(int nl, int nc);
  ~BMatrix();
  
public:  //getters
  int get_nl() const { return nl_; }
  int get_nc() const { return nc_; }
  double * get_data() const {return data_;}
  double operator()(int l, int c) const;
  bool same_size(const BMatrix & m) const;


public:  //setters
  double & operator()(int l, int c);

public: //operators
  BMatrix & operator+=(const BMatrix & m);
  BMatrix & operator-=(const BMatrix & m);
  BMatrix & operator=(const BMatrix & m);


  friend std::ostream& operator<<(std::ostream& st, const BMatrix& m);
  friend BMatrix operator+(const BMatrix & m1, const BMatrix & m2);
  friend BMatrix operator-(const BMatrix & m1, const BMatrix & m2);
  friend BMatrix operator*(const BMatrix & m1, const BMatrix & m2);
  friend BMatrix operator*(double val, const BMatrix & m);


};


#endif
