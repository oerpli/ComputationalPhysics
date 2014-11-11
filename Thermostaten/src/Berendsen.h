#pragma once
#include "Polymer.h"
ref class Berendsen{
private:
	Polymer& poly;
	double	dtime;
	double	target_temperature;
	double	couplingtime;
public:
	Berendsen(Polymer &poly, double dtime, double couplingtime);
	void	propagate();
};

