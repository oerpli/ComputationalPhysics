#pragma once

#include "Thermostat.h"
#include "Polymer.h"
#include<cmath>

class Thermostat_None : public Thermostat {

private:
	double m_dtime_half;

public:
	Thermostat_None(Polymer& poly, double delta_time);
	void	update_temp();
	void	dtime(double delta_time);
	void 	propagate();
};