#include "Nose_Hoover.h"

Nose_Hoover::Nose_Hoover(Polymer &a_polymer, double temperature, double relaxation_time) :
poly(a_polymer) {
	gkT = 3.0*(poly.Get_length() - 1.0)*temperature;
	q = gkT*relaxation_time*relaxation_time;
	eta = 0.0;
}

Nose_Hoover::~Nose_Hoover() {}

void Nose_Hoover::Propagate(double step) {
	double eta_new = 0.0;
	poly.Calculate_ekin();
	eta = (poly.Get_ekin() / 2.0 - gkT) / q;
	poly.Calculate_force();

	for (int i = 0; i < poly.Get_length(); i++) {
		poly.Set_monomer_position(i, poly.Get_monomer_position(i) + step*poly.Get_monomer_velocity(i) + step*step*0.5*(poly.Get_monomer_force(i) - eta*poly.Get_monomer_velocity(i)));
	}

	eta_new = eta + step*(poly.Get_ekin() - gkT*0.5) / q;

	for (int i = 0; i < poly.Get_length(); i++) {
		poly.Set_monomer_velocity(i, poly.Get_monomer_velocity(i) + step*0.5*(poly.Get_monomer_force(i) - eta*poly.Get_monomer_velocity(i)));
	}

	poly.Calculate_ekin();
	eta = eta_new + step*(poly.Get_ekin() - gkT*0.5) / q;
	poly.Calculate_force();

	for (int i = 0; i < poly.Get_length(); i++) {
		poly.Set_monomer_velocity(i, 2.0*(poly.Get_monomer_velocity(i) + step*0.5*poly.Get_monomer_force(i)) / (2.0 + step*eta));
	}

}

