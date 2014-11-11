#include "Nose_Hoover_Chain.h"

Nose_Hoover_Chain::Nose_Hoover_Chain(Polymer &a_polymer, double a_q1, double a_q2, double a_step) :
poly(a_polymer),
q1(a_q1),
q2(a_q2),
step(a_step),
xi1(0.0),
xi2(0.0),
nuxi1(0.0),
nuxi2(0.0),
g1(0.0),
g2(0.0) {
	stepd2 = 0.5*step;
	stepd4 = 0.5*stepd2;
	stepd8 = 0.5*stepd4;
	poly.update_forces();
}

Nose_Hoover_Chain::~Nose_Hoover_Chain() {}

void Nose_Hoover_Chain::pos_vel() {
	for (auto& m : poly.monomers) {
		m.velocity += m.force*stepd2 / poly.monomer_mass;
		m.position += m.velocity*step;
	}
	poly.update_forces();
	for (auto& m : poly.monomers) m.velocity += m.force*stepd2 / poly.monomer_mass;
}

void Nose_Hoover_Chain::chain() {
	poly.update_ekin();
	g2 = (q1*nuxi1*nuxi1 - poly.target_temperature()) / q2;
	nuxi2 += g2*stepd4;				// L_G2 
	nuxi1 *= exp(-nuxi2*stepd8);	// L_nuxi1
	g1 = (2.0*poly.ekin - (poly.monomers.size() - 1)*poly.target_temperature()) / q1;
	nuxi1 += g1*stepd4;				// L_G1
	nuxi1 *= exp(-nuxi2*stepd8);	// L_nuxi1
	xi1 += nuxi1*stepd2;			// L_xi
	xi2 += nuxi2*stepd2;			// L_xi
	double s = exp(-nuxi1*stepd2);

	for (auto& m : poly.monomers) m.velocity *= s;// L_Cv

	nuxi1 *= exp(-nuxi2*stepd8);	// L_nuxi1
	poly.update_ekin();
	g1 = (2.0*poly.ekin - (poly.monomers.size() - 1)*poly.target_temperature()) / q1;
	nuxi1 += g1*stepd4;				// L_G1
	nuxi1 *= exp(-nuxi2*stepd8);	// L_nuxi1
	g2 = (q1*nuxi1*nuxi1 - poly.target_temperature()) / q2;
	nuxi2 += g2*stepd4;				// L_G2 
}

void Nose_Hoover_Chain::propagate() {
	chain();
	pos_vel();
	chain();
}
