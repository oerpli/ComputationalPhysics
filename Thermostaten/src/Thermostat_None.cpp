#include "Thermostat_None.h"
#include <string>

const std::string Thermostat_None::m_name = "None";

Thermostat_None::Thermostat_None(Polymer& poly, double delta_time)
	: Thermostat(poly, delta_time) {
	update_temp();
	dtime(delta_time);
}

void Thermostat_None::update_temp() {
}

void Thermostat_None::dtime(double delta_time) {
	Thermostat::dtime(delta_time);
	m_dtime_half = m_dtime * 0.5;
}

void Thermostat_None::propagate() {
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime_half*m.force / m_poly.monomer_mass;
		m.position += m_dtime*m.velocity;
	}
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime_half*m.force / m_poly.monomer_mass;
	}
}

std::string Thermostat_None::name() const { return m_name; }

std::string Thermostat_None::info() const {
	std::string str{ "Thermostat " };
	str += m_name;
	str += " dtime ";
	str += std::to_string(m_dtime);
	return str;
}