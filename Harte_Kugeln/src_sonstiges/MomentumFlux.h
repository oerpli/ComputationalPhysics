/*
 * MomentumFlux.h
 *
 *  Created on: Jan 22, 2015
 *      Author: maud
 */

#ifndef SRC_SONSTIGES_MOMENTUMFLUX_H_
#define SRC_SONSTIGES_MOMENTUMFLUX_H_

#include "CollisionInfo.h"

template<unsigned DIM>
class MomentumFlux : public Auswert<struct CollisionInfo<DIM>> {
protected:
	velocitySquaredT momentum_flux;
	timeT measurement_time;
	double scale;

	//AverageVelocitySquared<DIM>& av_vel_sq_func;

public:
	/*MomentumFlux(lengthT diameter, unsigned N, AverageVelocitySquared<DIM>& func) : momentum_flux{},
	measurement_time{},
	scale{1./(3.*N*pow(double(diameter), 3))}, av_vel_sq_func{func} {}
*/

	void operator() (const struct CollisionInfo<DIM>& ci) {
		measurement_time = ci.system_time;
		timeT unit = 1.*s;
		if (ci.collision) {
			momentum_flux += (ci.delta_p_collision*ci.delta_v_collision)/unit;
		}
	}

	/*double value() {
		return (av_vel_sq_func.value()+double(momentum_flux*(1.*s)/measurement_time))*scale;
	}
*/
	double value() { return double(momentum_flux*(1.*s)/measurement_time); }
	std::ostream& print_result(std::ostream& os) {
		os << value() << " ";
		return os;
	}
};



#endif /* SRC_SONSTIGES_MOMENTUMFLUX_H_ */
