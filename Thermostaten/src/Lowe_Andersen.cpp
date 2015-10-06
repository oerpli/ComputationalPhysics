#include "Lowe_Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
#include "Rand.h"
using namespace consts;

#include <cmath>
#include <string>

using namespace std;

const string Lowe_Andersen::m_name = "Lowe_Andersen";

Lowe_Andersen::Lowe_Andersen(Polymer &poly, double delta_time, double nu) :
	Thermostat(poly, delta_time),
	m_nu(nu) {
	update_temp();
	dtime(delta_time);
}

void Lowe_Andersen::update_temp() {
	m_sigma = sqrt(2 * m_poly.target_temperature() / m_poly.monomer_mass);
}

void Lowe_Andersen::dtime(double dt) {
	Thermostat::dtime(dt);
	m_dtime2 = m_dtime * 0.5;
	m_nu_dt = m_nu*m_dtime*exp(-m_dtime*m_nu);
}

void Lowe_Andersen::propagate() {
	double therm_v = 0;
	auto mi = m_poly.monomers.begin();
	auto mj = mi;
	int direction{};

	// velocity verlet
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime2*m.force / m_poly.monomer_mass;
		m.position += m_dtime*m.velocity;
	}

	//Lowe_Andersen
	for (mi = m_poly.monomers.begin(); mi != m_poly.monomers.end(); ++mi) {
		if (m_nu_dt < Rand::real_uniform()) continue;

		mj = mi;
		++mj;
		if (mj == m_poly.monomers.end()) mj = m_poly.monomers.begin();
		therm_v = Rand::real_normal(0, m_sigma);

		direction = copysign(1, *mi - *mj);

		therm_v += direction * (mj->velocity - mi->velocity);
		therm_v *= direction * 0.5;

		mi->velocity += therm_v;
		mj->velocity -= therm_v;
	}

	// second half of vel. verlet
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime2*m.force / m_poly.monomer_mass;
	}
}

string Lowe_Andersen::name() const { return m_name; }

string Lowe_Andersen::info() const {
	string str{ "Thermostat " };
	str += m_name;
	str += " dtime ";
	str += to_string(m_dtime);
	str += " nu ";
	str += to_string(m_nu);
	return str;
}