#ifndef Polymer_H
#define Polymer_H

#include "Monomer.h"
#include "consts.h"

#include<cmath>
#include<iostream>
#include<vector>

class Polymer {
private:
	double	feder_konst, _temp;
	void    initiate_monomers_random(const int size);
        void    initiate_monomers_one(const int size);
	double	force(double r);
public:
	Polymer(int length, double temperature);
	~Polymer();
	std::vector<Monomer> monomers;
	std::ostream & print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...
	double	ekin, epot;
	double monomer_mass;

	double	temp();
	void	temp(double temperature);

	double	update_ekin();
	void	update_forces();
        
        double calculate_temp() const;
};
#endif
