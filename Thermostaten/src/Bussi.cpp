#include "Bussi.h"
#include "Polymer.h"
#include "Monomer.h"
#include "Thermostat.h"
#include "Rand.h"
#include <string>

const std::string Bussi::m_name = "Bussi";

Bussi::Bussi(Polymer &polymere, double timestep, double coupling_time)
	: Thermostat(polymere, timestep)
	, couplingtime(coupling_time)
{
	couplingtimeNfInverse = 1.0 / (couplingtime * m_poly.monomers.size());
	m_dtime_half = m_dtime * 0.5;
	target_ekin = m_poly.target_temperature() * m_poly.monomers.size() / 2.0;
}

void Bussi::propagate()
{
	//1. velocity verlet:
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime_half * m.force / m_poly.monomer_mass;
		m.position += m_dtime * m.velocity;
	}
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) m.velocity += m_dtime_half * m.force / m_poly.monomer_mass;

	//2. calculate target kinetic energy (as in the paper from bussi&donadio&parrinello)
	double ekin = m_poly.update_ekin();
	double wienernoise = Rand::real_normal() * m_dtime; // dW in the paper - N(0,1)
	double berendsen = (target_ekin - ekin)*m_dtime / couplingtime;
	double stochastic = 2.0* sqrt((ekin * target_ekin) * couplingtimeNfInverse) * wienernoise;
	double stoch_ekin = ekin + berendsen + stochastic; // evolve ekin with. stochastic dgl  (K_1 = K_0 + dK)
	//3. calculate scaling factor (as with gaussian thermostat)
	double scalingfactor;
	if (stoch_ekin > 0)
		scalingfactor = sqrt(stoch_ekin / ekin);
	else
		scalingfactor = -sqrt(-stoch_ekin / ekin);
	//4. rescale
	for (auto& m : m_poly.monomers) m.velocity *= scalingfactor;
}

void Bussi::update_temp() {
}

std::string Bussi::name() const { return m_name; }

std::string Bussi::info() const {
	std::string str{ "Thermostat " };
	str += m_name;
	str += " dtime ";
	str += std::to_string(m_dtime);
	str += " couplTime ";
	str += std::to_string(couplingtime);
	return str;
}