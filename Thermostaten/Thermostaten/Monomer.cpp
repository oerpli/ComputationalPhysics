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


std::ostream& Monomer::Print(std::ostream &os) const {
	os << position << "  " << velocity << "  " << force;
	return os;
}

double Monomer::Get_position() { return position; }
void 	Monomer::Set_position(double pos) { position = pos; }
void	Monomer::Set_velocity(double vel) { velocity = vel; }
void 	Monomer::Set_pos_vel(double pos, double vel) {
	Set_position(pos);
	Set_velocity(vel);
}

double Monomer::Distance(const Monomer & m_other) const {
	return this->position - m_other.position;
}
double Monomer::operator-(const Monomer & m_other) const{
	return this->Distance(m_other);
}

double Monomer::Get_force() { return force; }
void 	Monomer::Reset_force() { force = 0; }
double Monomer::Add_force(double df) { return force += df; }

double Monomer::Next_position(double dt) {
	return position += velocity*dt;
}

double Monomer::Next_velocity(double dt) {
	return velocity += force*dt; //m=1!
}
