#include "Nose_Hoover.h"

Nose_Hoover::Nose_Hoover(Polymer &a_polymer, double temperature, double relaxation_time) :
poly(a_polymer) {
	gkT = (poly.monomers.size() - 1.0)*temperature;
	q = gkT*relaxation_time*relaxation_time;
	eta = 0.0;
}

Nose_Hoover::~Nose_Hoover() {}

void Nose_Hoover::propagate(double step) {
        double stepsq = step*step; 
	poly.update_ekin();
	poly.update_forces();

	for (auto& m : poly.monomers){
		m.position += step*m.velocity + stepsq*.5*(m.force - eta*m.velocity);
		m.velocity += step*0.5*(m.force - eta*m.velocity);
	}

	eta += step*(poly.ekin - gkT*0.5) / q;
	poly.update_ekin();
	eta += step*(poly.ekin - gkT*0.5) / q;

	poly.update_forces();
	for (auto& m : poly.monomers)
		m.velocity = 2.0 * (m.velocity + step*0.5*m.force) / (2.0 + step*eta);
}

