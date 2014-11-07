#include "Nose_Hoover.h"

Nose_Hoover::Nose_Hoover(Polymer &a_polymer, double a_temperature, double a_q, double a_step) :
poly(a_polymer),
q(a_q),
step(a_step),
stepsq(a_step*a_step) {
	gkT = (poly.monomers.size() - 1.0)*a_temperature;
	eta = 0.0;
	poly.update_ekin();
	poly.update_forces();
}

Nose_Hoover::~Nose_Hoover() {}

void Nose_Hoover::propagate() {
	for (auto& m : poly.monomers){
	        m.position += step*m.velocity + stepsq*.5*((m.force / poly.monomer_mass) - eta*m.velocity);
		m.velocity += step*0.5*((m.force / poly.monomer_mass) - eta*m.velocity);
	}

	eta += step*(poly.ekin - gkT*0.5) / q;
	poly.update_ekin();
	eta += step*(poly.ekin - gkT*0.5) / q;

	poly.update_forces();
	for (auto& m : poly.monomers) m.velocity = 2.0 * (m.velocity + (step*0.5*m.force / poly.monomer_mass)) / (2.0 + step*eta);
	poly.update_ekin();
}

