#include "Bussi.h"
#include "Polymer.h"
#include "Monomer.h"
#include "Thermostat.h"
#include "Rand.h"
#include <string>
#include <algorithm>
#include "Consts.h"

const std::string Bussi::m_name = "Bussi";

Bussi::Bussi(Polymer &polymere, double timestep, double coupling_time)
	: Thermostat(polymere, timestep)
	, couplingtime(coupling_time)
{
	couplingtimeNfInverse = 1.0 / (couplingtime * m_poly.monomers.size());
	m_dtime_half = m_dtime * 0.5;
	target_ekin = m_poly.target_temperature() * m_poly.monomers.size() / 2.0;
}

void Bussi::propagate() // funktioniert jetzt einigermaßen
{
	static double k_ref_inverse = 1.0 / consts::ref_k;
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
	double stochastic = 2.0* sqrt(k_ref_inverse*(ekin * target_ekin) * couplingtimeNfInverse) * wienernoise;
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

void Bussi::propagate2() { //methode angelehnt an sample code - produziert deutlich zu geringe temperaturen
	//1. velocity verlet:
	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime_half * m.force / m_poly.monomer_mass;
		m.position += m_dtime * m.velocity;
	}
	m_poly.update_forces();
	for (auto& m : m_poly.monomers) m.velocity += m_dtime_half * m.force / m_poly.monomer_mass;
#if DEBUG
	if (m_poly.monomers.size() % 2 != 0) {
		cout << "Please fix chisquared generation" << endl;
		cout << "chisquaredfixed = Rand::real_gamma((m_poly.monomers.size() - 1) / 2, 1.0);" << endl;
	}
#endif
	auto Nf = m_poly.monomers.size();
	auto ekin = m_poly.update_ekin();
	auto expfactor = exp(-m_dtime / couplingtime);

	double chisquared = Rand::real_gamma((m_poly.monomers.size() - 2) / 2, 1.0) + pow(Rand::real_normal(), 2); // have to add 1 squared rand real normal bc Nf -1 is not even.
	auto normal = Rand::real_normal();

	auto ekinnew = ekin + (1.0 - expfactor)*(target_ekin *(chisquared + normal*normal) / Nf - ekin);
	ekinnew += 2.0 * normal  * sqrt(ekin*target_ekin / Nf*(1.0 - expfactor)*expfactor);
#if DEBUG
	if (ekinnew != ekinnew) {
		cout << "ALERT";
	}
	if (normal + sqrt(expfactor / rate) < 0.0) {
		scalingfactor = -scalingfactor;
	}
	if (expfactor + r1 + r2 < 0) {
		cout << "PROBLEM" << endl;
	}
#endif

	auto scalingfactor = sqrt(ekinnew / ekin);

	//3. rescale
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