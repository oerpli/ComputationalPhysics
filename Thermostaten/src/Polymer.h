#ifndef Polymer_H
#define Polymer_H

#include "Monomer.h"

#include<cmath>
#include<iostream>
#include<vector>

class Polymer {
private:
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
};
#endif
