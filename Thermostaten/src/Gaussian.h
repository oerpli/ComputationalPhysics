#pragma once
#include "Thermostat.h"
#include <string>

class Gaussian : public Thermostat {
private:
	double	m_dtime_half;
	static const std::string m_name;
public:
	Gaussian(Polymer &poly, double delta_time);
	void	update_temp();
	void	dtime(double delta_time);
	void	propagate();
	std::string name() const;
	std::string info() const;
};
