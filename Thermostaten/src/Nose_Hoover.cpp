#include "Nose_Hoover.h"

Nose_Hoover::Nose_Hoover(Polymer &a_polymer, double temperature, double relaxation_time) :
poly(a_polymer) {
	gkT = 3.0*(poly.Monomers.size() - 1.0)*temperature;
	q = gkT*relaxation_time*relaxation_time;
	eta = 0.0;
}

Nose_Hoover::~Nose_Hoover() {}

void Nose_Hoover::Propagate(double step) {
	double eta_new = 0.0;

	poly.Update_EKin();
	poly.Update_Forces();
	eta = (poly.Ekin / 2.0 - gkT) / q;

	for (auto& m : poly.Monomers){
		m.Position += step*m.Velocity + step*step*.5*(m.Force - eta*m.Velocity);
		m.Velocity += step*0.5*(m.Force - eta*m.Velocity);
	}

	eta_new = eta + step*(poly.Ekin - gkT * 0.5) / q;
	poly.Update_EKin();
	eta = eta_new + step*(poly.Ekin - gkT*0.5) / q;

	poly.Update_Forces();
	for (auto& m : poly.Monomers)
		m.Velocity = 2 * (m.Velocity + step*.5*m.Force) / (2. + step*eta);
}

