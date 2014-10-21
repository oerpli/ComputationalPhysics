#include "Monomer.h"

#include<iostream>
#include<cmath>
	
Monomer::Monomer() : position(0), velocity(0), force(0) {}
Monomer::Monomer(double pos, double vel) :
	position(pos), velocity(vel), force(0) {}
Monomer::Monomer(const Monomer &cSource) : 
	position(cSource.position), force(cSource.force), 
	velocity(cSource.velocity) {}

	
double Monomer::Get_position() {return position; }

std::ostream& Indi_1cr_1al_origin::Disp(std::ostream &os,int flag=0) {
	
	os << angles[0] << "  " << angles[1]<< endl;
	
	for (int i=0;i<5;i++)
		os<<variables[i]<<"  ";
	os << endl;
	
	if (flag != 1) {
		for (int i=0;i<basis_n-1;i++)
			os<<dp_basis[3*i+1] <<"  "<<dp_basis[3*i+1]<< "  " << dp_basis[3*i+1] << endl;
	}
	
	os << "Energy: " << pot_energy << " ; Fitness: " << fitness << endl;
return os;
}
