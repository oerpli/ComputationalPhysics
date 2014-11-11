#pragma once

#include "Thermostat.h"

#include<cmath>
#include "Polymer.h"

class Nose_Hoover : public Thermostat {

private:
	double m_q;
	double m_dtimesq;
	double m_gkT;
	double m_eta;

public:
	Nose_Hoover(Polymer& poly, double delta_time, double q);
	~Nose_Hoover();

	void	dtime(double new_dtime);
	void	update_temp();
	void	propagate();
};