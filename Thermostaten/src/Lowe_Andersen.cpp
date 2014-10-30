#include "Lowe_Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
using namespace consts;

#include<cmath>

using namespace std;

Lowe_Andersen::Lowe_Andersen(Polymer &poly, double dtime, double nu) : poly(poly),
  nu(nu), uniform_real(0.,1.), gauss_real(0.,1.) {
    
  time_step(dtime);
  update_sigma();
}

double Lowe_Andersen::update_sigma() {
  sigma=sqrt(2*ref_k*poly.temp()/poly.monomer_mass);
  
return sigma;
}

double  Lowe_Andersen::time_step() {return dtime;}

double  Lowe_Andersen::time_step(double dt) {
    dtime=dt;
    dtime2=dtime/2;
    nu_dt=nu*dtime;
    
return dtime;
}

void  Lowe_Andersen::propagate() {
  double delta_v=0, therm_v=0;
  auto  m_i= poly.monomers.begin();
  auto  m_j= m_i;
  
  // velocity verlet
  for (auto& m : poly.monomers) {
		m.velocity += dtime2*m.force/poly.monomer_mass;
		m.position += dtime*m.velocity;
	}

  //Lowe_Andersen
  for (m_i = poly.monomers.begin(); m_i != poly.monomers.end(); ++m_i) {
		if ( nu_dt < uniform_real(generator) ) continue;
    
    m_j=m_i;
    ++m_j;
    if ( m_j == poly.monomers.end() ) m_j=poly.monomers.begin();
    
    delta_v=m_i->velocity - m_j->velocity;
    therm_v=poly.monomer_mass*0.5*( delta_v - copysign( sigma, delta_v )*gauss_real(generator) );
    
    m_i->velocity += therm_v;
    m_j->velocity -= therm_v;
	}
  
  // second half of vel. verlet
	poly.update_forces();
	for (auto& m : poly.monomers) {
		m.velocity += dtime2*m.force/poly.monomer_mass;
	}
  

  
}
