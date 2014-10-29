#include "Polymer.h"

#include<cmath>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>

#include "consts.h"
using namespace consts;

void Polymer::initiate_monomer_array(const int size, double pos, double vel) {
	monomers = std::vector<Monomer>();
	for (int i = 0; i < size; i++){
		monomers.push_back(Monomer(0.0, drand48() - 0.5));
	}
}

Polymer::Polymer(int length, double temp) : epot(0) {
	monomer_mass=1./length;
	temperature=temp;		// damit beim monomer Inizialisieren bereits temperature vorhanden ist
	initiate_monomer_array(length, 0, 0);
	update_ekin();
	
	set_temp(temp);		// zum berechnen der Federkonstante
	
	double sum_velocity = 0.0;
	for (auto& m : monomers) { 
		sum_velocity += m.velocity; 
	}
	sum_velocity /= (double)length;
	for (auto& m : monomers) { 
	        m.velocity -= sum_velocity; 
	}
	update_ekin();
	double scale_factor = sqrt(temperature*((double)length - 1.)/ (2.*ekin));
	for (auto& m : monomers) {
	        m.velocity = m.velocity*scale_factor;
	}
}

Polymer::~Polymer() {}

double Polymer::get_temp() {return temperature;}

void		Polymer::set_temp(double temp) {
		temperature=temp;
		feder_konst=monomer_mass*pow(monomers.size()*temperature*ref_k/ref_hbar,2);
std::cout << "FederKonst: " << feder_konst << std::endl;
}

std::ostream & Polymer::print(std::ostream &os) const {
	for (auto& m : monomers) {
		print_m(m,os);
		os << std::endl;
	}
	return os;
}

double Polymer::force(double r) {return -r*feder_konst;}

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
	ekin *= 0.5;
	return ekin;
}
