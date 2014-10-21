#ifndef Monomer_H
#define Monomer_H

#include<iostream>

class Monomer {
	private:
		double position, velocity, force;
	
	public:
		Monomer();
		Monomer(double pos, double vel);
		Monomer(const Monomer &);

		std::ostream &os Print(std::ostream &os); //Wahrscheinlich besser Name Möglich...
			
		double Get_position();
		
		double Get_force();
		void   Reset_force();
		double Add_force(double df);
};
#endif
