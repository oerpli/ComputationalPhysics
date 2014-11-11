#include "Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
#include "Rand.h"
using namespace consts;

#include<cmath>

using namespace std;

Andersen::Andersen(Polymer &poly, double delta_time, double nu) :
Thermostat(poly, delta_time),
m_nu(nu) {
	update_temp();
	dtime(delta_time);
}

void Andersen::update_temp() {
	m_sigma = sqrt(m_poly.target_temperature() / m_poly.monomer_mass);
}

void Andersen::dtime(double dt) {
	Thermostat::dtime(dt);
	m_dtime2 = m_dtime * 0.5;
	m_nu_dt = m_nu*m_dtime;
}

void  Andersen::propagate() {
	// velocity verlet
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime2*m.force / m_poly.monomer_mass;
		m.position += m_dtime*m.velocity;
	}

	m_poly.update_forces();

	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime2*m.force / m_poly.monomer_mass;
	}

	//Andersen
	for (auto& m : m_poly.monomers) {
		if (m_nu_dt > Rand::real_uniform())
			m.velocity = m_sigma*Rand::real_normal();
	}
}
