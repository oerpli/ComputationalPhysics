#ifndef Polymer_H
#define Polymer_H

#include "Monomer.h"

#include<cmath>
#include<iostream>
#include<vector>

class Polymer {
private:
	//Monomer *A_monomer;
	void Initiate_monomer_array(int, double pos, double vel);
	void Initiate_polymer_std();
	double Force(double r);
public:
	std::vector<Monomer> Monomers;
	double Temp_soll, Ekin, Epot;
	Polymer(int);
	~Polymer();
	std::ostream & Print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...

	void Update_EKin();
	void Update_Forces();


	//Polymer();
	//Polymer(int len, double pos, double vel);

	//void Next_position(double dt);
	//void Next_velocity(double dt);


	//int Get_length();
	//double Get_ekin();
	//double Get_monomer_position(int);
	//double Get_monomer_velocity(int);
	//double Get_monomer_force(int);

	//void Set_monomer_position(int, double);
	//void Set_monomer_velocity(int, double);

	//int 	Get_position(double *& array) const;
	//int 	Get_velocity(double *& array) const;
	//int 	Get_force(double *& array) const;
	//void	Set_position(double *& array, int length);
	//void	Set_velocity(double *& array, int length);
};
#endif
