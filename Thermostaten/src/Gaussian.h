#pragma once

#include "Thermostat.h"

#include "Polymer.h"

class Gaussian : public Thermostat {
private:
	double	m_target_temperature;
	double	m_dtime_half;
public:
	Gaussian(Polymer &poly, double delta_time);
	void	update_temp();
	void	dtime(double delta_time);
	void	propagate();
};
