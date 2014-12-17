#include <iostream>
#include <vector>
#include "MatVec.h"

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>

using namespace boost::units;
using namespace boost::units::si;

template <unsigned DIM>
class Kugel {
	quantity<mass> m_mass; //mass ist nun ein Datentyp
	quantity<length> m_diameter;
public:
	MatVec<quantity<length>,DIM> vec_pos;
	MatVec<quantity<velocity>,DIM> vec_vel; //velocity ist nun ein Datentyp
	//collision next_collision;

	Kugel();
	Kugel(const Kugel<DIM> & kugel);
	Kugel(quantity<mass> m_mass, quantity<length> d);

	friend void swap(Kugel<DIM>& kugelA, Kugel<DIM>& kugelB) {
			swap(kugelA.vec_pos, kugelB.vec_pos); //swap von MatVec
			swap(kugelA.vec_vel, kugelB.vec_vel); //swap von MatVec
			std::swap(kugelA.mass, kugelB.mass);
			std::swap(kugelA.diameter, kugelB.diameter);
	}

	std::ostream& print(std::ostream & os = std::cout) const;


};


#include "Kugel.cpp"


