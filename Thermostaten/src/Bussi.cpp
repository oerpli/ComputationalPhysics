#include "Bussi.h"
#include "Polymer.h"
#include "Monomer.h"
#include "Rand.h"

Bussi::Bussi(Polymer &polymere, double timestep, double coupling_time)
	: poly(polymere)
	, dtime(timestep)
	, couplingtime(coupling_time){
}

//1. propagate 1 timestep with velocity verlet
//2. calculate e_kin and evolve it with stochastic dynamics
//3. rescale velocities
void Bussi::propagate() {
	//1. velocity verlet: 
	auto dtimehalf = dtime*0.5;
	for (auto& m : poly.monomers) {
		m.velocity += dtimehalf * m.force / poly.monomer_mass;
		m.position += dtime * m.velocity;
	}
	poly.update_forces();
	for (auto& m : poly.monomers) m.velocity += dtimehalf * m.force / poly.monomer_mass;

	//2. calculate scaling factor
	auto expfactor = exp(-dtime / couplingtime);
	auto ekin = poly.update_ekin();
	auto currenttemp = poly.calculate_temp();
	auto temperature_ratio = poly.target_temperature() / currenttemp;
	auto rate = (1.0 - expfactor)*temperature_ratio / poly.monomers.size();
	auto r = Rand::real_normal();
	double s = 0.0;
	for (int i = 0; i < poly.monomers.size(); i++) s += pow(Rand::real_normal(), 2);
	double scalingfactor = sqrt(expfactor + (s + pow(r, 2)) * rate + 2.0 * r *sqrt(expfactor*rate));
	if (r + sqrt(expfactor / rate) < 0.0) scalingfactor = -scalingfactor;
	//3. rescale 
	for (auto& m : poly.monomers) m.velocity *= scalingfactor;
}