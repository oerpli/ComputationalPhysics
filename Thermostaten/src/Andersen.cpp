#include "Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
using namespace consts;

#include<cmath>

using namespace std;

Andersen::Andersen(Polymer &poly, double dtime, double nu) : poly(poly),
  nu(nu), uniform_real(0.,1.), gauss_real(0.,1.) {
    
  time_step(dtime);
  update_sigma();
}

double Andersen::update_sigma() {
  sigma=sqrt(ref_k*poly.temp()/poly.monomer_mass);
  
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
  
  //Andersen
  for (auto& m : poly.monomers) {
		if (nu_dt > uniform_real(generator))
      m.velocity=sigma*gauss_real(generator);
	}
  
}
