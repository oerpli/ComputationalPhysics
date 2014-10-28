#ifndef Polymer_H
#define Polymer_H

#include "Monomer.h"

#include<cmath>
#include<iostream>
#include<vector>

class Polymer {
private:
	void initiate_monomer_array(int, double pos, double vel);
	void initiate_polymer_std();
	double force(double r);
public:
	std::vector<Monomer> monomers;
	double temperature, ekin, epot;
	Polymer(int);
	~Polymer();
	std::ostream & print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...

	double update_ekin();
	void update_forces();
};
#endif
