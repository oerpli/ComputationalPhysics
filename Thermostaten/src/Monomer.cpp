#include "Monomer.h"

#include<iostream>
#include<cmath>

using namespace std;

Monomer::Monomer() {position=velocity=force=0;}
Monomer::Monomer(double pos, double vel) {
	position=pos;
	velocity=vel;
	force=0;
}

double operator-(const Monomer & m1, const Monomer &m2) {
	return m1.position - m2.position;
}

std::ostream& print_m(const Monomer &mono, std::ostream &os) {
	os << mono.position << "  " << mono.velocity << "  " << mono.force;
	return os;
}
