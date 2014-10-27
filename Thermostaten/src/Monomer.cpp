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
//double Monomer::Get_position() { return position; }
//double Monomer::Get_velocity() { return velocity; }
//void 	Monomer::Set_position(double pos) { position = pos; }
//void	Monomer::Set_velocity(double vel) { velocity = vel; }


//double Monomer::Get_force() { return force; }
//void 	Monomer::Reset_force() { force = 0; }
//double Monomer::Add_force(double df) { return force += df; }

//double Monomer::Next_position(double dt) {
//	return position += velocity*dt;
//}

//double Monomer::Next_velocity(double dt) {
//	return velocity += force*dt; //m=1!
//}
