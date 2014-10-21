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

double Monomer::Get_position() {return position; }
void 	Monomer::Set_position(double pos) {position=pos;}
void	Monomer::Set_velocity(double vel) {velocity=vel;}
void 	Monomer::Set_pos_vel(double pos, double vel) {
	Set_position(pos);
	Set_velocity(vel);
}
