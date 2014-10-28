#include "Polymer.h"

#include<cmath>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>


void Polymer::initiate_monomer_array(const int size, double pos, double vel) {
	monomers = std::vector<Monomer>();
	for (int i = 0; i < size; i++){
		monomers.push_back(Monomer(0.0, rand() % 5));
	}
}

void Polymer::initiate_polymer_std() {
	temperature = 1.0;
	ekin = epot = 0;
}


Polymer::Polymer(int length) {
	initiate_polymer_std();
	initiate_monomer_array(length, 0, 0);
	double sum_velocity = 0.0;
	for (auto& m : monomers) {
		sum_velocity += m.velocity;
	}
	sum_velocity /= length;
	update_ekin();
	double scale_factor = sqrt(temperature*((double)length - 1.)/ (2.*ekin));
	for (auto& m : monomers) {
		m.velocity = (m.velocity - sum_velocity)*scale_factor;
	}
}

Polymer::~Polymer() {}

std::ostream & Polymer::print(std::ostream &os) const {
	for (auto& m : monomers) {
		print_m(m,os);
		os << std::endl;
	}
	return os;
}

double Polymer::force(double r) {//LJ
	double k = 1;
	return r*k;
}

void Polymer::update_forces() {
	//wahrscheinlich durch Optimierung der nächsten Schleife unnötig
	for (auto& m : monomers){
		m.force = 0;
	}
	unsigned int size = monomers.size();
	for (unsigned int i = 1; i <= size; i++) {
		double force_buf = force(monomers[i - 1] - monomers[i % size]);
		monomers[i - 1].force += force_buf; //bin mir da mit dem Vorzeichen nicht sicher!
		monomers[i % size].force -= force_buf;
	}
}

double Polymer::update_ekin(){
	ekin = 0.0;
	for (auto& m : monomers) {
		ekin += m.velocity*m.velocity; //mass = 1 
	}
	ekin /= 2.0;
return ekin;
}
