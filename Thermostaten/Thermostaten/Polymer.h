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
	Polymer(int len, double pos, double vel);
	~Polymer();

	std::ostream & Print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...

	void Calculate_force();
	void Next_position(double dt);
	void Next_velocity(double dt);
	void Calculate_ekin(); 

	int Get_length(); 
	double Get_ekin(); 
	double Get_monomer_position(int); 
	double Get_monomer_velocity(int); 
	double Get_monomer_force(int); 

	void Set_monomer_position(int, double); 
	void Set_monomer_velocity(int, double); 
	
	int 	Get_position(double *& array) const;
	int 	Get_velocity(double *& array) const;
	int 	Get_force(double *& array) const;
	void	Set_position(double *& array,int length);
	void	Set_velocity(double *& array,int length);
};
#endif
