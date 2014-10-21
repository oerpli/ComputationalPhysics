#include "Monomer.h"

#include<iostream>
#include<cmath>

using namespace std;

Monomer::Monomer() : position(0), velocity(0), force(0) {}
Monomer::Monomer(double pos, double vel) :
	position(pos), velocity(vel), force(0) {}
Monomer::Monomer(const Monomer &cSource) : 
	position(cSource.position), force(cSource.force), 
	velocity(cSource.velocity) {}

	
double Monomer::Get_position() {return position; }

std::ostream& Monomer::Print(std::ostream &os) const {
	os << position << "  " << velocity << "  " << force;
return os;
}
