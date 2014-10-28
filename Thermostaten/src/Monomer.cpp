#include "Monomer.h"

#include<iostream>
#include<cmath>

using namespace std;

Monomer::Monomer() : Position(0), Velocity(0), Force(0) {}
Monomer::Monomer(double pos, double vel) : Position(pos), Velocity(vel), Force(0) {}
Monomer::Monomer(const Monomer &cSource) : Position(cSource.Position), Force(cSource.Force), Velocity(cSource.Velocity) {}




double Monomer::Distance(const Monomer & m_other) const {
	return Position - m_other.Position;
}

double Monomer::operator-(const Monomer & m_other) const{
	return Distance(m_other);
}

std::ostream& Monomer::Print(std::ostream &os) const {
	os << Position << "  " << Velocity << "  " << Force;
	return os;
}
