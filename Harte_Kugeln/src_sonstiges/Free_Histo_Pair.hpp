#ifndef FREE_HISTO_PAIR_HPP_
#define FREE_HISTO_PAIR_HPP_

#include <cmath>

#include "Free_Histo.h"

class Free_Histo_Pair : public Free_Histo {
private:
	const double m_scale_pair;

public:
	Free_Histo_Pair() : Free_Histo{}, m_scale_pair{} {}
	Free_Histo_Pair(double width, double rho, unsigned N) : Free_Histo{width}, m_scale_pair{ N*3.0/(2.0*M_PI*rho)} {}

	virtual bool output(std::ostream& os) {
		os.precision(8);
		os << std::scientific;
		os << histo_iter->first << '\t';
		os << (histo_iter->second) * scale * m_scale_pair / pow(histo_iter->first,2) << '\t';
		os << std::flush;
		auto histo_iter_buf = histo_iter;
		if (++histo_iter_buf == histo.end())
			return false;

		++histo_iter;
		return true;
	}

};

#endif // FREE_HISTO_PAIR_HPP_
