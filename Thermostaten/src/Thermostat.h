#ifndef Thermostat_H
#define Thermostat_H

#include "Polymer.h"

class Thermostat {

protected:
	Polymer& m_poly;
	double m_dtime;
	
public:
	Thermostat(Polymer &poly, double delta_time);
	
	double dtime() const;
	double	dtime(double new_dtime);
	double update_temp();	// für mögliche Erwärmung
	
	void propagate();
};

#endif
