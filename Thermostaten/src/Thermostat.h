#pragma once
#include "Polymer.h"

class Thermostat {


protected:
	Polymer& m_poly;
	double m_dtime;
public:
	Thermostat(Polymer &poly, double delta_time);

	double dtime() const;
	virtual void dtime(double new_dtime);
	virtual void update_temp() = 0;	// für mögliche Erwärmung
	virtual void propagate() = 0;
};
