#include "Polymer.h"

#include<cmath>
#include<iostream>
#include<stdlib.h>

void Polymer::Initiate_monomer_array(double pos, double vel) {
	delete A_monomer;
<<<<<<< a978db21cce4976d575a5e942d124bea1220d57c
	A_monomer = new Monomer[A_length];

	if (pos != 0 && vel != 0)
		for (int i = 0; i < A_length; i++)
			A_monomer[i].Set_pos_vel((rand() % 5)*9. / 10, 0);//A_monomer[i].Set_pos_vel(pos,vel);
=======
	A_monomer = new Monomer [A_length];
	
	if (pos != 0 && vel != 0) 
		for (int i=0;i<A_length;i++)
			A_monomer[i].Set_pos_vel((rand()%5)+0,0);//A_monomer[i].Set_pos_vel(pos,vel);
>>>>>>> e5c34e90663e99905fd195e57d38f3c2e3eb52f5
}

void Polymer::Initiate_polymer_std() {
	A_length = 0;
	A_monomer = 0;
	Temp_soll = 0;
	Ekin = Epot = 0;
}

Polymer::Polymer() {
	Initiate_polymer_std();
	Initiate_monomer_array(0, 0);
}

Polymer::Polymer(int len) {
	Initiate_polymer_std();
	A_length = len;
	Initiate_monomer_array(0, 0);
}

Polymer::Polymer(int len, double pos, double vel) {
	Initiate_polymer_std();
	A_length = len;
	Initiate_monomer_array(pos, vel);
}

Polymer::~Polymer() { delete[] A_monomer; A_monomer = 0; }

std::ostream & Polymer::Print(std::ostream &os) const {
	for (int i = 0; i < A_length; i++) {
		A_monomer[i].Print(os);
		os << std::endl;
	}
	return os;
}

<<<<<<< a978db21cce4976d575a5e942d124bea1220d57c
double Polymer::Force(double r) {
	double s = 1, e = 1, sr6 = pow(s / r, 6);
	if (r == 0)
=======
/*
double Polymer::Force(double r) {//LJ
	double s=1, e=1, sr6=pow(s/r,6);
	if (r==0)
>>>>>>> e5c34e90663e99905fd195e57d38f3c2e3eb52f5
		return 0;
	return -24 * e*(2 * pow(sr6, 2) / r - sr6 / r);
}
*/

double Polymer::Force(double r) {//LJ
	double k=1;
return r*k;
}

void Polymer::Calculate_force() {
	int i = 0, force_buf = 0;

	//wahrscheinlich durch Optimierung der nächsten Schleife unnötig
	for (i = 0; i < A_length; i++)
		A_monomer[i].Reset_force();
<<<<<<< a978db21cce4976d575a5e942d124bea1220d57c

	for (i = 1; i < A_length; i++) {
		force_buf = Force(A_monomer[i - 1] - A_monomer[i]);
		A_monomer[i - 1].Add_force(force_buf); //bin mir da mit dem Vorzeichen nicht sicher!
		A_monomer[i].Add_force(-force_buf);
	}
	force_buf = Force(A_monomer[A_length - 1] - A_monomer[0]);
	A_monomer[A_length - 1].Add_force(force_buf); //bin mir da mit dem Vorzeichen nicht sicher!
=======
	
	for (i=1;i<A_length;i++) {
		force_buf=Force(A_monomer[i-1]-A_monomer[i]);
		//force_buf=A_monomer[i-1]-A_monomer[i];
		A_monomer[i-1].Add_force(force_buf); //bin mir da mit dem Vorzeichen nicht sicher!
		A_monomer[i].Add_force(-force_buf);
	}
	force_buf=Force(A_monomer[A_length-1]-A_monomer[0]);
	//force_buf=A_monomer[A_length-1]-A_monomer[0];
	A_monomer[A_length-1].Add_force(force_buf); //bin mir da mit dem Vorzeichen nicht sicher!
>>>>>>> e5c34e90663e99905fd195e57d38f3c2e3eb52f5
	A_monomer[0].Add_force(-force_buf);
}


void Polymer::Next_position(double dt){
	for (int i = 0; i < A_length; i++)
		A_monomer[i].Next_position(dt);
}

void Polymer::Next_velocity(double dt){
	for (int i = 0; i < A_length; i++)
		A_monomer[i].Next_velocity(dt);
}

