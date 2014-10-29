#ifndef Polymer_H
#define Polymer_H

#include "Monomer.h"
#include "consts.h"

#include<cmath>
#include<iostream>
#include<vector>

class Polymer {
private:
	double	feder_konst, monomer_mass;
	double	temperature;
	void	initiate_monomer_array(int, double pos, double vel);
	void	initiate_polymer_std();
	double	force(double r);
public:
	Polymer(int length, double temp);
	~Polymer();
	std::vector<Monomer> monomers;
	std::ostream & print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...
	double	ekin, epot;

	double	get_temp();
	void	set_temp(double temp);

	double	update_ekin();
	void	update_forces();
};
#endif
