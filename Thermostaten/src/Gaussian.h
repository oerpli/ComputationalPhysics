#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include "Thermostat.h"

#include "Polymer.h"

class Gaussian : Thermostat{
private:
	double	m_target_temperature;
	double m_dtime_half;
public:
	Gaussian(Polymer &poly, double delta_time);
	double	update_temp();
	double dtime(double delta_time);
	void    propagate();
};
#endif 

