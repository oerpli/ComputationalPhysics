#pragma once

#include "Thermostat.h"

#include "consts.h"

#include <cmath>
#include <string>

class Lowe_Andersen : public Thermostat {
private:
	double m_dtime2;
	double m_nu, m_nu_dt, m_sigma;
	static const std::string m_name;
public:
	double time;

	Lowe_Andersen(Polymer &poly, double dtime, double nu);

	void	dtime(double delta_time);
	void	update_temp();
	void	propagate();
	std::string name() const;
	std::string info() const;
};
