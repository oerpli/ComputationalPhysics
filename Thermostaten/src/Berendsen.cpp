#include "Berendsen.h"
#include "Polymer.h"
#include "Monomer.h"

Berendsen::Berendsen(Polymer &polymere, double timestep, double coupling_time)
	: poly(polymere)
	, dtime(timestep)
	, couplingtime(coupling_time){
}

//1. propagate 1 timestep with velocity verlet
//2. calculate scaling factor from temperature difference and coupling time (coupling time = 0 => gaussian)
//3. rescale velocities
void Berendsen::propagate() {
	//1. velocity verlet: 
	auto dtimehalf = dtime*0.5;
	for (auto& m : poly.monomers) {
		m.velocity += dtimehalf * m.force / poly.monomer_mass;
		m.position += dtime * m.velocity;
	}
	poly.update_forces();
	for (auto& m : poly.monomers) m.velocity += dtimehalf * m.force / poly.monomer_mass;

	//2. calculate scaling factor
	auto ekin = poly.update_ekin();
	auto scalingfactor = sqrt(1 + dtime / couplingtime * (poly.target_temperature() / poly.calculate_temp() - 1));

	//3. rescale 
	for (auto& m : poly.monomers)m.velocity *= scalingfactor;
}