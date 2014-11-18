#pragma once
#include "Thermostat.h"
#include <string>

class Bussi : public Thermostat {
private:
	double	target_temperature;
	double	couplingtime;
	static const std::string m_name;
public:
	Bussi(Polymer &poly, double dtime, double couplingtime);

	void	update_temp();
	void	propagate();
	std::string name() const;
	std::string info() const;
};
