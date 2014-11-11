#pragma once

#include "Thermostat.h"
#include "Polymer.h"
#include "consts.h"

#include<cmath>

class Andersen : public Thermostat {
private:
	double	m_dtime2;
	double	m_nu, m_nu_dt, m_sigma;
public:
	double	time;

	Andersen(Polymer &poly, double dtime, double nu);

	void	dtime(double dt);
	void	update_temp();
	void	propagate();
};