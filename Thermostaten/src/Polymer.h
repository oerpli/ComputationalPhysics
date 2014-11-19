#ifndef Polymer_H
#define Polymer_H

#include "Monomer.h"
#include "consts.h"

#include<cmath>
#include<iostream>
#include <vector>
#include <string>

class Polymer {
private:
	double	m_feder_konst;
	double	m_target_temp;
	std::string	m_ini;
	double	force(double r) const;
public:
	Polymer(unsigned length, double temperature);
	~Polymer();
	std::vector<Monomer> monomers;
	std::ostream & print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...
	double	ekin, epot;
	double	monomer_mass;

	void	initiate_monomers_random();
	void	initiate_monomers_one();

	double	feder_konst() const;

	double	target_temperature() const;
	void	target_temperature(double temperature);

	double update_epot();
	double	update_ekin();
	void	update_forces();
	void	update_all();
	
	double calculate_temp() const;
	
	std::string ini() const;
	std::string info() const;
};
#endif
