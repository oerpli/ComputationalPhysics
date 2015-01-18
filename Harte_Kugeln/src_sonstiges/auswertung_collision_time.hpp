#ifndef AUSWERTUNG_COLLISION_TIME_HPP_
#define AUSWERTUNG_COLLISION_TIME_HPP_

#include "Auswert.h"
#include "CollisionPair.h"
#include "Free_Histo.h"

template<unsigned DIM>
class auswertung_collision_time : public Auswert<CollisionPair<DIM>> {
public:
	Free_Histo distribution;
	timeT time_buf{};

public:
	auswertung_collision_time() : auswertung_collision_time{0.0} {}
	auswertung_collision_time(double width) : distribution{width} {}

	void operator() (const CollisionPair<DIM>& cp) {
		time_buf += cp.collision_time();
		if (cp) {
			distribution(double(time_buf));
			time_buf = 0._s;
		}
	}

	double value() { return double(time_buf); }

	std::ostream& print_result(std::ostream& os) {
		bool out {};
	  	do {
		  	out = distribution.output(os);
		  	os << '\n';
	  	} while(out);
	  	distribution.output_reset();
		return os;
	}
};

#endif //AUSWERTUNG_COLLISION_TIME_HPP_
