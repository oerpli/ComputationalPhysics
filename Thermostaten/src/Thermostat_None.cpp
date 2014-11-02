#include "Thermostat_None.h"

Thermostat_None::Thermostat_None(Polymer& a_polymer, double a_step) :
poly(a_polymer),
step(a_step),
stepd2(0.5*a_step) {
	poly.update_forces();
}

Thermostat_None::~Thermostat_None() {}

void Thermostat_None::propagate() {
	for (auto& m : poly.monomers) {
		m.velocity += stepd2*m.force / poly.monomer_mass;
		m.position += step*m.velocity;
	}

	poly.update_forces();

	for (auto& m : poly.monomers) {
		m.velocity += stepd2*m.force / poly.monomer_mass;
	}
}

