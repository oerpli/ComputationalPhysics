#ifndef Monomer_H
#define Monomer_H

#include<cmath>

class Monomer {
	private:
		double position, force, velocity;
	
	public:
		double Get_position();
		
		double Get_force();
		void   Reset_force();
		double Add_force(double df);
}
#endif
