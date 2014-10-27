//#include "Nose_Hoover.h"
//
//Nose_Hoover::Nose_Hoover(Polymer &a_polymer, double temperature, double relaxation_time) :
//poly(a_polymer) {
//	gkT = 3.0*(poly.Get_length() - 1.0)*temperature;
//	q = gkT*relaxation_time*relaxation_time;
//	eta = 0.0;
//}
//
//Nose_Hoover::~Nose_Hoover() {}
//
//void Nose_Hoover::Propagate(double step) {
//	int i, length;
//	double eta_new = 0.0;
//	double *A_position = 0, *A_velocity = 0, *A_force = 0;
//
//	poly.Calculate_ekin();
//	eta = (poly.Get_ekin() / 2.0 - gkT) / q;
//	poly.Calculate_force();
//
//	length = poly.Get_position(A_position);
//	poly.Get_velocity(A_velocity);
//	poly.Get_force(A_force);
//
//	for (i = 0; i < length; i++)
//		A_position[i] = A_position[i] + step*A_velocity[i] + step*step*.5*(A_force[i] - eta*A_velocity[i]);
//
//	eta_new = eta + step*(poly.Get_ekin() - gkT*0.5) / q;
//
//	for (i = 0; i < length; i++)
//		A_velocity[i] = A_velocity[i] + step*0.5*(A_force[i] - eta*A_velocity[i]);
//
//	poly.Set_position(A_position, length);
//	poly.Set_velocity(A_velocity, length);
//
//	poly.Calculate_ekin();
//	eta = eta_new + step*(poly.Get_ekin() - gkT*0.5) / q;
//	poly.Calculate_force();
//
//	poly.Get_force(A_force);
//
//	for (i = 0; i < length; i++)
//		A_velocity[i] = 2 * (A_velocity[i] + step*.5*A_force[i]) / (2. + step*eta);
//
//	poly.Set_velocity(A_velocity, length);
//
//	delete[] A_position;
//	delete[] A_velocity;
//	delete[] A_force;
//
//	return;
//}
//
