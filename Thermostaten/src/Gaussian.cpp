#include "Gaussian.h"
#include "Polymer.h"
#include "Monomer.h"
#include "consts.h"

using namespace consts;
using namespace std;


Gaussian::Gaussian(Polymer &polymere, double timestep)
	: poly(polymere)
	, dtime(timestep) {
}
//1. velocity verlet
//2. scale velocities to get desired energy
void Gaussian::propagate() {
	//1. velocity verlet
	auto dtimehalf = dtime*0.5;
	for (auto& m : poly.monomers) {
		m.velocity += dtimehalf*m.force / poly.monomer_mass;
		m.position += dtime*m.velocity;
	}
	poly.update_forces();
	for (auto& m : poly.monomers) m.velocity += dtimehalf*m.force / poly.monomer_mass;

	//2. scale velocities
	auto scalefactor = sqrt(poly.target_temperature() / (poly.update_ekin()*2. / poly.monomers.size()));
	for (auto& m : poly.monomers)m.velocity *= scalefactor;
}
