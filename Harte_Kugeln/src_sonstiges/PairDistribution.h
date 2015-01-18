/*
 * PairDistribution.h
 *
 *  Created on: Jan 15, 2015
 *      Author: maud
 */

#ifndef SRC_SONSTIGES_PAIRDISTRIBUTION_H_
#define SRC_SONSTIGES_PAIRDISTRIBUTION_H_


#include "Auswert.h"
#include "Kugel.h"
#include "Free_Histo_Pair.hpp"

template<unsigned DIM>
class PairDistribution : public Auswert<Kugel<DIM>, Kugel<DIM>, lengthT> {
private:
	Free_Histo_Pair distribution;

public:
	PairDistribution(double width, double rho, unsigned N);
	void operator ()(const Kugel<DIM>& k1, const Kugel<DIM>& k2, const lengthT& dist);
	std::ostream& print_result(std::ostream& os);
	double value();
};

#include "PairDistribution.tpp"

#endif /* SRC_SONSTIGES_PAIRDISTRIBUTION_H_ */
