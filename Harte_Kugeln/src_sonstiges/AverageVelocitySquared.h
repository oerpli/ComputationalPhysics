/*
 * AverageVelocitySquared.h
 *
 *  Created on: Jan 22, 2015
 *      Author: maud
 */

#ifndef SRC_SONSTIGES_AVERAGEVELOCITYSQUARED_H_
#define SRC_SONSTIGES_AVERAGEVELOCITYSQUARED_H_

// calculates average_sim(sum_i(v^2))
template<unsigned DIM>
class AverageVelocitySquared : public Auswert<Kugel<DIM>> {
protected:
	velocitySquaredT sum_vel_sq;
	unsigned count;

public:
	void operator() (const Kugel<DIM>& kugel) {
		sum_vel_sq += kugel.velocity().norm2();
		count++;
	}
	double value() { return double(sum_vel_sq)/count; }
	std::ostream& print_result(std::ostream& os) {
		os << value() << " ";
		return os;
	}
};


#endif /* SRC_SONSTIGES_AVERAGEVELOCITYSQUARED_H_ */
