#include "Monomer.h"

#include<iostream>
#include<cmath>

using namespace std;

Monomer::Monomer() : position(0), velocity(0), force(0) {}
Monomer::Monomer(double pos, double vel) : position(pos), velocity(vel), force(0) {}
Monomer::Monomer(const Monomer &cSource) : position(cSource.position), force(cSource.force), velocity(cSource.velocity) {}




double Monomer::distance(const Monomer & m_other) const {
	return position - m_other.position;
}

double Monomer::operator-(const Monomer & m_other) const{
	return distance(m_other);
}

std::ostream& Monomer::print(std::ostream &os) const {
	os << position << "  " << velocity << "  " << force;
	return os;
}
