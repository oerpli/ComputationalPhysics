#ifndef Monomer_H
#define Monomer_H

#include<iostream>

struct Monomer {
	double position;
	double velocity;
	double force;

	Monomer();
	Monomer(double pos, double vel);
};

double operator-(const Monomer & m1, const Monomer &m2);
std::ostream & print_m(const Monomer &mono, std::ostream &os); //Wahrscheinlich besser Name Möglich...

#endif

