#include "Gaussian.h"
#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"

using namespace consts;
using namespace std;


Gaussian::Gaussian(Polymer &poly, double delta_time)
	: Thermostat(poly, delta_time) {
	update_temp();
	dtime(delta_time);
}

void Gaussian::update_temp() {
	m_target_temperature = m_poly.target_temperature();
}

void Gaussian::dtime(double delta_time) {
	Thermostat::dtime(delta_time);
	m_dtime_half = m_dtime * 0.5;
}

void  Gaussian::propagate() {
	// velocity verlet //kopiert von thermostat_none::propagate()
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime_half*m.force / m_poly.monomer_mass;
		m.position += m_dtime*m.velocity;
	}
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime_half*m.force / m_poly.monomer_mass;
	}
	auto scalefactor = sqrt(m_target_temperature / (m_poly.update_ekin()*2. / m_poly.monomers.size()));
	for (auto& m : m_poly.monomers)m.velocity *= scalefactor;//velocity rescaling
}
