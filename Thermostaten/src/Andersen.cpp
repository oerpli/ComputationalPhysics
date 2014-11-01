#include "Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
using namespace consts;

#include<cmath>

using namespace std;

Andersen::Andersen(Polymer &poly, double dtime, double nu) : m_poly(poly),
  m_nu(nu), uniform_real(0.,1.), gauss_real(0.,1.) {
    
  time_step(dtime);
  update_sigma();
}

double Andersen::update_sigma() {
  m_sigma=sqrt(ref_k*m_poly.temp()/m_poly.monomer_mass);
  
return m_sigma;
}

double  Andersen::time_step() {return m_dtime;}

double  Andersen::time_step(double dtime) {
    m_dtime=dtime;
    m_dtime2=m_dtime/2;
    m_nu_dt=m_nu*m_dtime;
    
return m_dtime;
}

void  Andersen::propagate() {
  // velocity verlet
  for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime2*m.force/m_poly.monomer_mass;
		m.position += m_dtime*m.velocity;
	}

	m_poly.update_forces();

	for (auto& m : m_poly.monomers) {
		m.velocity += m_dtime2*m.force/m_poly.monomer_mass;
	}
  
  //Andersen
  for (auto& m : m_poly.monomers) {
		if (m_nu_dt > uniform_real(generator))
      m.velocity=m_sigma*gauss_real(generator);
	}
  
}
