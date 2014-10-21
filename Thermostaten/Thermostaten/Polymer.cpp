#include "Polymer.h"

#include<cmath>
#include<iostream>

void Polymer::Initiate_monomer_array(double pos, double vel) {
	delete A_monomer;
	A_monomer = new Monomer [A_length];
	
	if (pos != 0 && vel != 0) 
		for (int i=0;i<A_length;i++)
			A_monomer[i].Set_pos_vel(pos,vel);
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
