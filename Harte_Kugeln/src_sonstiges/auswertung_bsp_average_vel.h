#ifndef AUSWERTUNG_BSP_AVERAGE_VEL_H_
#define AUSWERTUNG_BSP_AVERAGE_VEL_H_

#include "Auswert.h"
#include "Kugel.h"

template<unsigned DIM>
class auswertung_bsp_average_vel : public Auswert<Kugel<DIM>> {
public:
	velocityT sum_vel;
	unsigned count;

public:
	void operator() (const Kugel<DIM>& k) {
		sum_vel += k.velocity().norm();
		count++;
	}
	double value() { return double(sum_vel) / count; }
	std::ostream& print_result(std::ostream& os) {
		os << value() << " ";
		return os;
	}
};

#endif //AUSWERTUNG_BSP_AVERAGE_VEL_H_
