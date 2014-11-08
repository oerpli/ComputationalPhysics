#ifndef ANDERSEN_H
#define ANDERSEN_H

#include "Thermostat.h"
#include "Polymer.h"
#include "consts.h"

#include<cmath>

class Andersen : Thermostat {
private:
	double m_dtime2;
	double m_nu, m_nu_dt, m_sigma;
public:
	double time;

	Andersen(Polymer &poly, double dtime, double nu);

	double	dtime(double delta_time);
	double	update_temp();
	void		propagate();
};
#endif 

