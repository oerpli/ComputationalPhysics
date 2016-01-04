#include "Gaussian.h"
#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
#include <string>

using namespace consts;
using namespace std;

const string Gaussian::m_name = "Gaussian";

Gaussian::Gaussian(Polymer &poly, double delta_time)
	: Thermostat(poly, delta_time) {
	dtime(delta_time);
	zeta = 0.0; 
}

void Gaussian::update_temp() {
}

void Gaussian::dtime(double delta_time) {
	Thermostat::dtime(delta_time);
	m_dtime_half = m_dtime * 0.5;
}

void Gaussian::propagate() {
  // new implementation based on Neumann's script CP2 
  zeta = 0.0;
  double denom = 0.0;
  std::vector<double> vel_dt2; 
  m_poly.update_forces();
  for (auto& m : m_poly.monomers) {
    vel_dt2.push_back(m.velocity+m_dtime_half*m.force/m_poly.monomer_mass);
    zeta += vel_dt2.back()*m.force;
    denom += vel_dt2.back()*vel_dt2.back(); 
  }
  denom *= m_poly.monomer_mass; 
  zeta /= denom; 
  for (unsigned i = 0; i < m_poly.monomers.size(); i++) {
    m_poly.monomers[i].velocity += m_dtime*(m_poly.monomers[i].force/m_poly.monomer_mass - zeta*vel_dt2[i]);
    m_poly.monomers[i].position += m_dtime*m_poly.monomers[i].velocity; 
  }  
}

  
string Gaussian::name() const { return m_name; }

string Gaussian::info() const {
	string str{ "Thermostat " };
	str += m_name;
	str += " dtime ";
	str += to_string(m_dtime);
	return str;
}
