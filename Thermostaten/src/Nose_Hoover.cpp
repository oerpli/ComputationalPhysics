#include "Nose_Hoover.h"
#include <cmath>
#include <string>

const std::string Nose_Hoover::m_name = "Nose_Hoover";

Nose_Hoover::Nose_Hoover(Polymer &poly, double delta_time, double q) :
	Thermostat(poly, delta_time),
	m_q(q),
	m_eta(0.0)
{
	update_temp();
	dtime(delta_time);
	poly.update_ekin();
	poly.update_forces();
}

Nose_Hoover::~Nose_Hoover() {}

void Nose_Hoover::update_temp() {
	m_gkT = (m_poly.monomers.size() - 1.0)*m_poly.target_temperature();
}

void Nose_Hoover::dtime(double delta_time) {
	Thermostat::dtime(delta_time);
	m_dtimesq = pow(m_dtime, 2);
}

void Nose_Hoover::propagate() {
	for (auto& m : m_poly.monomers) {
		m.position += m_dtime*m.velocity + m_dtimesq*.5*((m.force / m_poly.monomer_mass) - m_eta*m.velocity);
		m.velocity += m_dtime*0.5*((m.force / m_poly.monomer_mass) - m_eta*m.velocity);
	}

	m_eta += m_dtime*(m_poly.ekin - m_gkT*0.5) / m_q;
	m_poly.update_ekin();
	m_eta += m_dtime*(m_poly.ekin - m_gkT*0.5) / m_q;

	m_poly.update_forces();
	for (auto& m : m_poly.monomers) m.velocity = 2.0 * (m.velocity + (m_dtime*0.5*m.force / m_poly.monomer_mass)) / (2.0 + m_dtime*m_eta);
	m_poly.update_ekin();
}

std::string Nose_Hoover::name() const { return m_name; }

std::string Nose_Hoover::info() const {
	std::string str{ "Thermostat " };
	str += m_name;
	str += " dtime ";
	str += std::to_string(m_dtime);
	str += " q ";
	str += std::to_string(m_q);
	return str;
}