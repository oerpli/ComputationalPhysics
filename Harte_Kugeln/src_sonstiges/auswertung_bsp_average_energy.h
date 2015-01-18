#ifndef AUSWERTUNG_BSP_AVERAGE_ENERGY_H_
#define AUSWERTUNG_BSP_AVERAGE_ENERGY_H_

#include "Auswert.h"
#include "Kugel.h"

template<unsigned DIM>
class auswertung_bsp_average_energy : public Auswert<Kugel<DIM>> {
public:
	energyT sum_energy;
	unsigned count;

public:
	void operator() (const Kugel<DIM>& k) {
		sum_energy += k.ekin();
		count++;
	}
	double value() { return double(sum_energy) / count; }
	std::ostream& print_result(std::ostream& os) {
		os << value() << " ";
		return os;
	}
};

#endif //AUSWERTUNG_BSP_AVERAGE_ENERGY_H_
