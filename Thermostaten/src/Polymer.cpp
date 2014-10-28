#include "Polymer.h"

#include<cmath>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>


//blubb blubb blubb...check, ob adressänderung funktioniert hat

void Polymer::Initiate_monomer_array(const int size, double pos, double vel) {
	Monomers = std::vector<Monomer>();
	for (int i = 0; i < size; i++){
		Monomers.push_back(Monomer(i, rand() % 5));
	}
}

void Polymer::Initiate_polymer_std() {
	Temp_soll = 0;
	Ekin = Epot = 0;
}


Polymer::Polymer(int length) {
	Initiate_polymer_std();
	Initiate_monomer_array(length, 0, 0);
	double Sum_velocity = 0.0;
	for (auto& m : Monomers) {
		Sum_velocity += m.Velocity;
	}
	Sum_velocity /= length;
	Update_EKin();
	double Scale_factor = sqrt(Temp_soll*length / Ekin);
	for (auto& m : Monomers) {
		m.Velocity = (m.Velocity - Sum_velocity)*Scale_factor;
	}
}

Polymer::~Polymer() {}

std::ostream & Polymer::Print(std::ostream &os) const {
	for (auto& m : Monomers) {
		m.Print(os);
		os << std::endl;
	}
	return os;
}

double Polymer::Force(double r) {//LJ
	double k = 1;
	return r*k;
}

void Polymer::Update_Forces() {
	//wahrscheinlich durch Optimierung der nächsten Schleife unnötig
	for (auto& m : Monomers){
		m.Force = 0;
	}
	unsigned int size = Monomers.size();
	for (unsigned int i = 1; i <= size; i++) {
		double force_buf = Force(Monomers[i - 1] - Monomers[i % size]);
		Monomers[i - 1].Force += force_buf; //bin mir da mit dem Vorzeichen nicht sicher!
		Monomers[i % size].Force -= force_buf;
	}
}

void Polymer::Update_EKin(){
	Ekin = 0.0;
	for (auto& m : Monomers) {
		Ekin += m.Velocity*m.Velocity; //mass = 1 
	}
	Ekin /= 2.0;
}
