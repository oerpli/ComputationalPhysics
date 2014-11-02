#include "Lowe_Andersen.h"

#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"
#include "Rand.h"
using namespace consts;

#include<cmath>

using namespace std;

Lowe_Andersen::Lowe_Andersen(Polymer &poly, double dtime, double nu) : poly(poly), nu(nu){
	time_step(dtime);
	update_sigma();
}

double Lowe_Andersen::update_sigma() {
	sigma = sqrt(2 * ref_k*poly.temp() / poly.monomer_mass);
	return sigma;
}

double  Lowe_Andersen::time_step() { return dtime; }

double  Lowe_Andersen::time_step(double dt) {
	dtime = dt;
	dtime2 = dtime / 2;
	nu_dt = nu*dtime;

	return dtime;
}

void  Lowe_Andersen::propagate() {
	double delta_v = 0, therm_v = 0;
	auto  mi = poly.monomers.begin();
	auto  mj = mi;

	// velocity verlet
	for (auto& m : poly.monomers) {
		m.velocity += dtime2*m.force / poly.monomer_mass;
		m.position += dtime*m.velocity;
	}

	//Lowe_Andersen
	for (mi = poly.monomers.begin(); mi != poly.monomers.end(); ++mi) {
		if (nu_dt < Rand::real_uniform()) continue;

		mj = mi;
		++mj;
		if (mj == poly.monomers.end()) mj = poly.monomers.begin();

		delta_v = mi->velocity - mj->velocity;
		therm_v = poly.monomer_mass*0.5*(delta_v - copysign(sigma, delta_v)*Rand::real_normal());

		mi->velocity += therm_v;
		mj->velocity -= therm_v;
	}

	// second half of vel. verlet
	poly.update_forces();
	for (auto& m : poly.monomers) {
		m.velocity += dtime2*m.force / poly.monomer_mass;
	}



}
