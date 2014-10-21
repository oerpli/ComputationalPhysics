#include "Monomer.h"

#include<cmath>
	
Monomer::Monomer() : position(0), force(0), velocity(0) {}
Monomer::Monomer(const Monomer &cSource) : 
	position(cSource.position), force(cSource.force), 
	velocity(cSource.velocity) {}
~Monomer();

	
double Monomer::Get_position() {return position; }
