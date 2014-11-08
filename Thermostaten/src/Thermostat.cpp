#include "Thermostat.h"
#include "Polymer.h"

Thermostat::Thermostat(Polymer &poly, double delta_time) : m_poly(poly) {
	dtime(delta_time);
}

double Thermostat::dtime() const { return m_dtime; }

double Thermostat::dtime(double new_dtime) { return m_dtime = new_dtime;}
