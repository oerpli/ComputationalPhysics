#include "Bussi.h"
#include "Polymer.h"
#include "Monomer.h"
#include "Thermostat.h"
#include "Rand.h"
#include <string>


const std::string Bussi::m_name = "Bussi";

Bussi::Bussi(Polymer &polymere, double timestep, double coupling_time)
	: Thermostat(polymere, timestep)
	, couplingtime(coupling_time){
}

//1. propagate 1 timestep with velocity verlet
//2. calc. scaling factor
//3. rescale velocities
void Bussi::propagate() {
	//1. velocity verlet: 
	auto dtimehalf = m_dtime*0.5;
	for (auto& m : m_poly.monomers) {
		m.velocity += dtimehalf * m.force / m_poly.monomer_mass;
		m.position += m_dtime * m.velocity;
	}
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) m.velocity += dtimehalf * m.force / m_poly.monomer_mass;

	//2. calculate scaling factor
	auto currenttemp = m_poly.calculate_temp();
	auto temperature_ratio = m_poly.target_temperature() / currenttemp;

	auto expfactor = exp(-m_dtime / couplingtime);

	auto rate = (1.0 - expfactor)*temperature_ratio / m_poly.monomers.size();
	double sum = 0.0;
	for (unsigned i = 1; i < m_poly.monomers.size(); i++){ // n-1 times
		sum += pow(Rand::real_normal(), 2);
	}
	auto r = Rand::real_normal();
	auto r1 = (sum + pow(r, 2)) * rate;
	auto r2 = 2.0 * r *sqrt(expfactor*rate);
	auto  scalingfactor = sqrt(expfactor + r1 + r2);
	if (r + sqrt(expfactor / rate) < 0.0) {
		scalingfactor = -scalingfactor;
	}
	//3. rescale 
	for (auto& m : m_poly.monomers) m.velocity *= scalingfactor;
}


void Bussi::update_temp(){
}

std::string Bussi::name() const {return m_name;}

std::string Bussi::info() const {
	std::string str{"Thermostat "};
	str += m_name;
	str += " dtime ";
	str += std::to_string ( m_dtime );
	str += " couplTime ";
	str += std::to_string ( couplingtime );
return str;
}
