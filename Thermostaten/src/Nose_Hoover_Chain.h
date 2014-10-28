#ifndef Nose_Hoover_Chain_H
#define Nose_Hoover_Chain_H

#include<cmath> 
#include "Polymer.h"

class Nose_Hoover_Chain {

 private: 
  Polymer& poly; 
  double temperature, q1, q2, step, xi1, xi2, nuxi1, nuxi2, g1, g2, stepd2, stepd4, stepd8; 
 
 public: 
  Nose_Hoover_Chain(Polymer&, double, double, double, double); 
  ~Nose_Hoover_Chain(); 

  void chain(); 
  void pos_vel(); 
  void propagate();
 
};
#endif
