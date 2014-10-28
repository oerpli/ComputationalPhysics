#ifndef Monomer_H
#define Monomer_H

#include<iostream>

class Monomer {
private:
	double distance(const Monomer & m_other) const;

public:
	double position, velocity, force;
	Monomer();
	Monomer(double pos, double vel);
	Monomer(const Monomer &);

	double operator-(const Monomer & m_other) const;
	std::ostream & print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...
};
#endif

