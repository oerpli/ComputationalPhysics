#include <iostream>
#include <vector>
#include <algorithm>
//Bin noch nicht so vertraut mit Units, hab einfach mal einige reingeladen...
#include <boost/units/cmath.hpp>
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>

#include <typeinfo>

#include "MatVec.h"
#include "Kugel.h"

template<typename T, unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MatVec<T,DIM>& vec);

using namespace std;
using namespace boost::units;
using namespace boost::units::si;


// Vectoren elementweise mulitiplizieren
// Scilab: vec1.*vec2
template<typename T1, typename T2, unsigned DIM>
auto operator* (const MatVec<T1, DIM>& vec1, const MatVec<T2, DIM>& vec2) -> MatVec<decltype( T1{} * T2{} ), DIM> {
	  MatVec<decltype( T1{} * T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = vec1[i] * vec2[i];
	  return result;
}

int main() {

	quantity<force> forceScalar = 3 * newton;
	MatVec<quantity<force>, 3> forceVec { forceScalar };
	quantity<length> lengthScalar = 3 * meter;
	MatVec<quantity<length>, 3> lengthVec { lengthScalar };

	forceVec[1] = 5 * newton;

	cout << forceVec << '\n';

	for (auto& el : lengthVec) cout << el << ' ';
	cout << '\n';

	const unsigned dim {4};
	cout << '\n' << "Kugelbeispiele mit Dimension " << dim << ":" << '\n';

	Kugel<dim> k1{}, k2{ (3*kilogram),(.5*meter)};
	Kugel<dim> k3{k2};

	cout << '\n' << "k1 Standard:" << '\n';
	k1.print();

	cout << '\n' << "k2:" << '\n';
	k2.print();

	cout << '\n' << "k3 Copy k2:" << '\n';
	k3.print();

}
