#pragma once
#include "Thermostat.h"
class Berendsen : public Thermostat{
private:
	double	couplingtime;
public:
	Berendsen(Polymer &poly, double dtime, double couplingtime);
	void	propagate();
	void	update_temp();
};

