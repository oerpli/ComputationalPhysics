#pragma once
#include "Thermostat.h"

class Bussi : public Thermostat {
private:
	double	target_temperature;
	double	couplingtime;
public:
	Bussi(Polymer &poly, double dtime, double couplingtime);

	void	update_temp();
	void	propagate();
};