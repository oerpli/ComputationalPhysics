/*
 * Autocorrelation.h
 *
 *  Created on: Jan 29, 2015
 *      Author: maud
 */

#ifndef SRC_SONSTIGES_AUTOCORRELATION_H_
#define SRC_SONSTIGES_AUTOCORRELATION_H_

#include "Auswert.h"
#include "Kugel.h"
#include <vector>
#include <list>

template<unsigned DIM>
class Autocorrelation : public Auswert<Kugel<DIM>> {
protected:
	unsigned number_of_entries;
	unsigned number_of_spheres;
	timeT time_resolution;
	unsigned sphere_counter;
	unsigned counter;
	std::vector<double> autocorrelation;
	std::vector<std::list<MatVec<velocityT, DIM>>> velocities;

public:
	Autocorrelation(unsigned N_c, unsigned N_k, timeT dt) : number_of_entries{N_c},
	number_of_spheres{N_k}, time_resolution{dt}, sphere_counter{0}, counter{0},
	autocorrelation(number_of_entries, 0.), velocities(number_of_spheres, std::list<MatVec<velocityT,DIM>>{}) {}

	void calculate() {
		for (auto& vel_list : velocities) {
			unsigned i {0};
			MatVec<velocityT, DIM> vel_zero = vel_list.front();
			for (auto& vel : vel_list ) {
				autocorrelation[i] += double(vel_zero*vel);
				i++;
			}
		}
		counter++;
	}

	void operator() (const Kugel<DIM>& k) {
		if (velocities[sphere_counter].size() == number_of_entries) velocities[sphere_counter].pop_front();
		velocities[sphere_counter].push_back(k.velocity());
		sphere_counter++;
		sphere_counter = sphere_counter % number_of_spheres;
		if (sphere_counter == 0) calculate();
	}

	double value() {
		double diffusion_constant {};
		for (auto& c : autocorrelation) {
			diffusion_constant += c*double(time_resolution)/(number_of_spheres*counter);
		}
		diffusion_constant /= 3.;
		return diffusion_constant;
	}

	std::ostream& print_result(std::ostream& os) {
		os << "\n #diffusion constant = " << value() << '\n';
		for (unsigned i = 0; i < autocorrelation.size(); i++) {
			os << i*double(time_resolution) << '\t' << autocorrelation[i]/(number_of_spheres*counter) << '\n';
		}
		return os;
	}

};
#endif /* SRC_SONSTIGES_AUTOCORRELATION_H_ */
