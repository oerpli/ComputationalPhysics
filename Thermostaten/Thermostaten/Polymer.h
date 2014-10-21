#ifndef Polymer_H
#define Polymer_H

#include "Monomer.h"

#include<cmath>
#include<iostream>

class Polymer {
	private:
		int A_length;
		Monomer *A_monomer;
		double Temp_soll, Ekin, Epot;
		
		void Initiate_monomer_array(double pos, double vel);
		void Initiate_polymer_std();
		
		double Force(double r);
		
	public:
		Polymer();
		Polymer(int len);
		Polymer(int len,double pos, double vel);
		~Polymer();

		std::ostream & Print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...
		
		void Calculate_force();
		void Next_position(double dt);
		void Next_velocity(double dt);
};
#endif
