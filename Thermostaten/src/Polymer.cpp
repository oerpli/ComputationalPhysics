#include "Polymer.h"

#include<cmath>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<numeric>
#include "consts.h"
using namespace consts;
using namespace std;

void Polymer::initiate_monomers_random() {
	double av_velocity = 0.0;
	for (auto& m : monomers)
		av_velocity += m.velocity = drand48() - 0.5;

	av_velocity /= monomers.size();

	for (auto& m : monomers) {
		m.velocity -= av_velocity;
	}

	update_ekin();

	double scale_factor = sqrt(_temp*monomers.size() / ekin*0.5*ref_k);
	for (auto& m : monomers) {
		m.velocity = m.velocity*scale_factor;
	}
}

void Polymer::initiate_monomers_one(const int size) { //erstes Monomer großteil der Energie
	double max_vel = sqrt((size - 1)*ref_k*_temp / monomer_mass);   
        monomers = std::vector<Monomer>(size, Monomer(0.0, -max_vel/(size-1)) );
        
	monomers[0].velocity = max_vel;
}

Polymer::Polymer(int length, double temperature) : _temp(temperature) , epot(0) {
	monomer_mass = 1. / length;
	initiate_monomers_one(length);
        
	temp(temperature);
}

Polymer::~Polymer() {}

double Polymer::temp() { return _temp; }

void Polymer::temp(double temperature) {
	_temp = temperature;
	feder_konst = monomer_mass * pow(monomers.size() * _temp * ref_k / ref_hbar, 2);
}

std::ostream & Polymer::print(std::ostream &os) const {
	for (auto& m : monomers) {
		print_m(m, os);
		os << std::endl;
	}
	return os;
}

double Polymer::force(double r) { return -r*feder_konst; }

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
	ekin *= monomer_mass*0.5;
	return ekin;
}

double Polymer::calculate_temp() const {
	double av_velocity = 0, av_energy = 0;

	for (auto& m : monomers)
		av_velocity += m.velocity;
	av_velocity /= monomers.size();

	for (auto& m : monomers)
		av_energy += pow(m.velocity - av_velocity, 2);
	av_energy *= monomer_mass / 2 / monomers.size();

	return av_energy / (0.5*ref_k);
}
