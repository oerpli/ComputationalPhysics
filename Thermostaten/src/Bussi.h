#pragma once
#include "Polymer.h"
ref class Bussi{
private:
	Polymer& poly;
	double	dtime;
	double	target_temperature;
	double	couplingtime;
	double	calc_scalingfactor();
public:
	Bussi(Polymer &poly, double dtime, double couplingtime);
	void	propagate();
};

