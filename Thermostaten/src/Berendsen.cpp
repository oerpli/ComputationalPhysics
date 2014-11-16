#include "Berendsen.h"
#include "Polymer.h"
#include "Monomer.h"

Berendsen::Berendsen(Polymer &polymere, double timestep, double coupling_time)
	: Thermostat(polymere, timestep)
	, couplingtime(coupling_time){
}

//1. propagate 1 timestep with velocity verlet
//2. calculate scaling factor from temperature difference and coupling time (coupling time = 0 => gaussian)
//3. rescale velocities
void Berendsen::propagate() {
	//1. velocity verlet: 
	auto dtimehalf = m_dtime*0.5;
	for (auto& m : m_poly.monomers) {
		m.velocity += dtimehalf * m.force / m_poly.monomer_mass;
		m.position += m_dtime * m.velocity;
	}
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) m.velocity += dtimehalf * m.force / m_poly.monomer_mass;

	//2. calculate scaling factor
	auto ekin = m_poly.update_ekin();
	auto scalingfactor = sqrt(1 + m_dtime / couplingtime * (m_poly.target_temperature() / m_poly.calculate_temp() - 1));

	//3. rescale 
	for (auto& m : m_poly.monomers)m.velocity *= scalingfactor;
}

void Berendsen::update_temp(){

}