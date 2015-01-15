#include "Free_Histo.h"

void Free_Histo::add(double val, unsigned i) {
	double klass { floor(val / width + 0.5) * (width) };
	histo[klass] += i;
	histo_iter = histo.begin();
	count++;
	scale = 1. / (width * count);
}

Free_Histo::Free_Histo() :
		Free_Histo { 1 } {
}

Free_Histo::Free_Histo(double width) :
		histo { }, histo_iter { }, width { width }, scale { }, count { } {
}

void Free_Histo::operator ()(double val) {
	add(val, 1);
}

bool Free_Histo::output(std::ostream& os) {
	os.precision(8);
	os << std::scientific;
	os << histo_iter->first << '\t';
	os << (histo_iter->second) * scale << '\t';
	os << std::flush;
	auto histo_iter_buf = histo_iter;
	if (++histo_iter_buf == histo.end())
		return false;

	++histo_iter;
	return true;
}



void Free_Histo::output_reset() {
	histo_iter = histo.begin();
}
