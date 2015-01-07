#ifndef AUSWERTUNG_BSP_AVERAGE_VEL_H_
#define AUSWERTUNG_BSP_AVERAGE_VEL_H_

#include "Auswert.h"
#include "Kugel.h"

#include <ostream>

template<unsigned DIM>
class auswertung_bsp_average_vel : public Auswert<Kugel<DIM>> {
public:
	velocityT sum_vel;
	unsigned count;

public:
	void operator() (const Kugel<DIM>& k) {
std::cout << "auwertung_bsp_average_vel.operator()" << 	'\n';
		sum_vel += k.velocity().norm();
		count++;
	}
	double value() { return (sum_vel/mps) / count; }
	std::ostream& print_result(std::ostream& os) {
		os << value() << " ";
		return os;
	}
};

#endif //AUSWERTUNG_BSP_AVERAGE_VEL_H_
