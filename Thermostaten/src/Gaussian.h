#pragma once
#include "Polymer.h"

class Gaussian {
private:
	Polymer& poly;
	double	dtime;
public:
	Gaussian(Polymer &poly, double timestep);
	void    propagate();
};

