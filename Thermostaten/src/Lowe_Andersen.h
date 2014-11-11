#ifndef LOWE_ANDERSEN_H
#define LOWE_ANDERSEN_H

#include "Thermostat.h"

#include "consts.h"

#include<cmath>

class Lowe_Andersen : public Thermostat {
private:
	double m_dtime2;
	double m_nu, m_nu_dt, m_sigma;
public:
	double time;

	Lowe_Andersen(Polymer &poly, double dtime, double nu);

	void	dtime(double delta_time);
	void	update_temp();
	void	propagate();
};
#endif 

