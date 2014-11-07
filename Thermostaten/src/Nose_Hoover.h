#ifndef Nose_Hoover_H
#define Nose_Hoover_H

#include<cmath>
#include "Polymer.h"

class Nose_Hoover {

private:
	Polymer& poly;
	double q;
	double step;
	double stepsq;
	double gkT;
	double eta;

public:
	Nose_Hoover(Polymer&, double, double);
	~Nose_Hoover();

	void propagate();
};
#endif 

