#include "Gaussian.h"
#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"

using namespace consts;
using namespace std;


Gaussian::Gaussian(Polymer &polymere, double timestep) : poly(polymere), dtime(timestep) {
	target_temperature = poly.temp();
}

void  Gaussian::propagate() {
	auto dtimehalf = dtime*0.5;
	// velocity verlet //kopiert von thermostat_none::propagate()
	for (auto& m : poly.monomers) {
		m.velocity += dtimehalf*m.force / poly.monomer_mass;
		m.position += dtime*m.velocity;
	}
	poly.update_forces();
	for (auto& m : poly.monomers) {
		m.velocity += dtimehalf*m.force / poly.monomer_mass;
	}
	auto scalefactor = sqrt(target_temperature / (poly.update_ekin()*2./poly.monomers.size()));
	for (auto& m : poly.monomers)m.velocity *= scalefactor;//velocity rescaling
}
