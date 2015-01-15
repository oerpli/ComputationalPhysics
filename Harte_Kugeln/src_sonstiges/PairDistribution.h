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
#include "Free_Histo.h"

template<unsigned DIM>
class PairDistribution : public Auswert<Kugel<DIM>, Kugel<DIM>> {
private:
	Free_Histo distribution;

public:
	PairDistribution(double width);
	void operator ()(const Kugel<DIM>& k1, const Kugel<DIM>& k2);
	std::ostream& print_result(std::ostream& os);
	double value();
};

#include "PairDistribution.tpp"

#endif /* SRC_SONSTIGES_PAIRDISTRIBUTION_H_ */
