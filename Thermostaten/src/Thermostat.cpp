#include "Thermostat.h"
#include "Polymer.h"

Thermostat::Thermostat(Polymer &poly, double delta_time) : m_poly(poly) {
	dtime(delta_time);
}

double Thermostat::dtime() const {
	return m_dtime;
}

void Thermostat::dtime(double new_dtime) {
	m_dtime = new_dtime;
}
