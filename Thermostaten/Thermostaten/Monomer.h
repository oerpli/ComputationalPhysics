#ifndef Monomer_H
#define Monomer_H

#include<iostream>

class Monomer {
	private:
		double position, velocity, force;
	
		double Distance(const Monomer & m_other) const;
		
	public:
		Monomer();
		Monomer(double pos, double vel);
		Monomer(const Monomer &);

		std::ostream & Print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...
			
		double Get_position();
		void 	Set_position(double pos);
		
		void	Set_velocity(double vel);
		
		void	Set_pos_vel(double pos, double vel);
		
		double	Get_force();
		void  	Reset_force();
		double	Add_force(double df);
		double operator-(const Monomer & m_other) const;
		
		double Next_position(double dt);
		double Next_velocity(double dt);
};
#endif

