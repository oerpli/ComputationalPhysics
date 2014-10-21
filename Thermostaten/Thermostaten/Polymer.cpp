#include "Polymer.h"

#include<cmath>
#include<iostream>
#include<stdlib.h>

void Polymer::Initiate_monomer_array(double pos, double vel) {
	delete A_monomer;
	A_monomer = new Monomer [A_length];
	
	if (pos != 0 && vel != 0) 
		for (int i=0;i<A_length;i++)
			A_monomer[i].Set_pos_vel((rand()%5)*9./10,0);//A_monomer[i].Set_pos_vel(pos,vel);
}

void Polymer::Initiate_polymer_std() {
	A_length=0;
	A_monomer=0;
	Temp_soll=0;
	Ekin=Epot=0;
}

Polymer::Polymer() {
	Initiate_polymer_std();
	Initiate_monomer_array(0,0);
}
	
Polymer::Polymer(int len) {
	Initiate_polymer_std();
	A_length=len;
	Initiate_monomer_array(0,0);
}

Polymer::Polymer(int len,double pos, double vel) {
	Initiate_polymer_std();
	A_length=len;
	Initiate_monomer_array(pos,vel);
}

Polymer::~Polymer() { delete[] A_monomer; A_monomer = 0;}

std::ostream & Polymer::Print(std::ostream &os) const {
	for (int i=0;i<A_length;i++) {
		A_monomer[i].Print(os);
		os << std::endl;
	}
return os;
}

double Polymer::Force(double r) {
	double s=1, e=1, sr6=pow(s/r,6);
	if (r==0)
		return 0;
return -24*e*(2*pow(sr6,2)/r-sr6/r);
}

void Polymer::Calculate_force() {
	int i=0, force_buf=0;
	
	//wahrscheinlich durch Optimierung der nächsten Schleife unnötig
	for (i=0;i<A_length;i++) 
		A_monomer[i].Reset_force();
	
	for (i=1;i<A_length;i++) {
		force_buf=Force(A_monomer[i-1]-A_monomer[i]);
		A_monomer[i-1].Add_force(force_buf); //bin mir da mit dem Vorzeichen nicht sicher!
		A_monomer[i].Add_force(-force_buf);
	}
	force_buf=Force(A_monomer[A_length-1]-A_monomer[0]);
	A_monomer[A_length-1].Add_force(force_buf); //bin mir da mit dem Vorzeichen nicht sicher!
	A_monomer[0].Add_force(-force_buf);
}


void Polymer::Next_position(double dt){
	for (int i=0;i<A_length;i++)
		A_monomer[i].Next_position(dt);
}

void Polymer::Next_velocity(double dt){
	for (int i=0;i<A_length;i++)
		A_monomer[i].Next_velocity(dt);
}

