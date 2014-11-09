#include "Lowe_Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
#include "Rand.h"
using namespace consts;

#include<cmath>

using namespace std;

Lowe_Andersen::Lowe_Andersen(Polymer &poly, double delta_time, double nu) :
Thermostat(poly,delta_time), 
m_nu(nu){
	dtime(delta_time);
}

double Lowe_Andersen::update_temp() {
	m_sigma = sqrt(2 * m_poly.temp() / m_poly.monomer_mass);
	return m_sigma;
}

double  Lowe_Andersen::dtime(double dt) {
	dtime(dt);
	m_dtime2 = m_dtime * 0.5;
	m_nu_dt = m_nu*m_dtime;
	return m_dtime;
}

void  Lowe_Andersen::propagate() {
	double delta_v = 0, therm_v = 0;
	auto  mi = m_poly.monomers.begin();
	auto  mj = mi;

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

		delta_v = mi->velocity - mj->velocity;
		therm_v = m_poly.monomer_mass*0.5*(delta_v - copysign(m_sigma, delta_v)*Rand::real_normal());

		mi->velocity += therm_v;
		mj->velocity -= therm_v;
	}

	// second half of vel. verlet
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime2*m.force / m_poly.monomer_mass;
	}
}
