#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include "Polymer.h"

class Gaussian {
private:
	Polymer& poly;
	double	dtime;
	double	target_temperature;
public:
	Gaussian(Polymer &poly, double timestep);
	void    propagate();
};
#endif 

