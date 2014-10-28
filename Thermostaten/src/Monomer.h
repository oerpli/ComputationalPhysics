#ifndef Monomer_H
#define Monomer_H

#include<iostream>

class Monomer {
private:
	double Distance(const Monomer & m_other) const;

public:
	double Position, Velocity, Force;
	Monomer();
	Monomer(double pos, double vel);
	Monomer(const Monomer &);

	double operator-(const Monomer & m_other) const;
	std::ostream & Print(std::ostream &os) const; //Wahrscheinlich besser Name Möglich...
};
#endif

