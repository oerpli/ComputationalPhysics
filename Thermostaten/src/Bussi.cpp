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
//2. calc. scaling factor
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
	auto scalingfactor = calc_scalingfactor();
	//3. rescale 
	for (auto& m : poly.monomers) m.velocity *= scalingfactor;
}

double Bussi::calc_scalingfactor(){
	auto currenttemp = poly.calculate_temp();
	auto temperature_ratio = poly.target_temperature() / currenttemp;

	auto expfactor = exp(-dtime / couplingtime);

	auto rate = (1.0 - expfactor)*temperature_ratio / poly.monomers.size();
	double s = 0.0;
	for (int i = 1; i < poly.monomers.size(); i++){ // n-1 times
		s += pow(Rand::real_normal(), 2);
	}
	auto r = Rand::real_normal();
	auto r1 = (s + pow(r, 2)) * rate;
	auto r2 = 2.0 * r *sqrt(expfactor*rate);
	double scalingfactor = sqrt(expfactor + r1 + r2);
	if (r + sqrt(expfactor / rate) < 0.0) scalingfactor = -scalingfactor;
}