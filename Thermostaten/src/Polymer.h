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
	double	ekin, epot, position, velocity;
	double	monomer_mass;

	void	initiate_monomers_random();
	void	initiate_monomers_one();

	double	feder_konst() const;

	double	target_temperature() const;
	void	target_temperature(double temperature);

	void	set_position(double pos = 0);
	void	set_velocity(double vel = 0);
	void	set_pos_vel(double pos = 0, double vel = 0);

	double update_epot();
	double	update_ekin();
	void	update_forces();
	double update_position();
	double update_velocity();
	void	update_all();

	double calculate_temp();

	std::string ini() const;
	std::string info() const;
};
#endif
