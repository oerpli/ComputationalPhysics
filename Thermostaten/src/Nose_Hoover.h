#ifndef Nose_Hoover_H
#define Nose_Hoover_H

#include "Thermostat.h"

#include<cmath>
#include "Polymer.h"

class Nose_Hoover : Thermostat {

private:
	double m_q;
	double m_dtimesq;
	double m_gkT;
	double m_eta;

public:
	Nose_Hoover(Polymer& poly , double delta_time, double q);
	~Nose_Hoover();

	double	dtime(double new_dtime);
	double update_temp();
	void propagate();
};
#endif 

