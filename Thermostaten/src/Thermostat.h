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
	virtual double	dtime(double new_dtime);
	virtual double update_temp() = 0;	// für mögliche Erwärmung
	
	virtual void propagate() = 0;
};

#endif
