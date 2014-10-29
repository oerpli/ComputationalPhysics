#ifndef Thermostat_None_H
#define Thermostat_None_H

#include "Polymer.h"
#include<cmath>

class Thermostat_None {

private:
	Polymer& poly;
	double step;
	double stepd2;

public:
	Thermostat_None(Polymer&, double);
	~Thermostat_None();

	void propagate();
};
#endif 
