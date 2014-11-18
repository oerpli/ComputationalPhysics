#pragma once
#include "Thermostat.h"
#include <string>

class Berendsen : public Thermostat{
private:
	double	couplingtime;
	static const std::string m_name;
public:
	Berendsen(Polymer &poly, double dtime, double couplingtime);
	void	propagate();
	void	update_temp();
	std::string name() const;
	std::string info() const;
};

