#include "Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
using namespace consts;

#include<cmath>

using namespace std;

Andersen::Andersen(Polymer &poly, double dtime, double nu) : poly(poly),
  nu(nu), uniform_real(0.,1.) {
    
  time_step(dtime);
  update_sigma();
}

double Andersen::update_sigma() {
  sigma=sqrt(ref_k*poly.temp()/poly.monomer_mass);
  
  // weiß grad keinen anderen Weg die Verteilung zu verändern...
  std::normal_distribution<double> gauss_buf(0.,sigma);
  gauss_real.param(gauss_buf.param());
  
return sigma;
}

double  Andersen::time_step() {return dtime;}

double  Andersen::time_step(double dt) {
    dtime=dt;
    dtime2=dtime/2;
    nu_dt=nu*dtime;
    
return dtime;
}

void  Andersen::propagate() {
  // velocity verlet
  
  for (auto& m : poly.monomers) {
		m.velocity += dtime2*m.force/poly.monomer_mass;
		m.position += dtime*m.velocity;
	}

	poly.update_forces();

	for (auto& m : poly.monomers) {
		m.velocity += dtime2*m.force/poly.monomer_mass;
	}
  
  for (auto& m : poly.monomers) {
		if (nu_dt < uniform_real(generator))
      continue;
    m.velocity=gauss_real(generator);
	}
  
}
