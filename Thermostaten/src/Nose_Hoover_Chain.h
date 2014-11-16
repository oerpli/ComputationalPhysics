#pragma once

#include<cmath> 
#include "Polymer.h"
#include "Thermostat.h"
class Nose_Hoover_Chain :public Thermostat {

private:
	double q1, q2, xi1, xi2, nuxi1, nuxi2, g1, g2, stepd2, stepd4, stepd8;

	void chain();
	void pos_vel();

public:
	Nose_Hoover_Chain(Polymer&, double, double, double);
	~Nose_Hoover_Chain();
	void propagate();
	void update_temp();
};
