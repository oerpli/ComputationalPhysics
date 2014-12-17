#include <iostream>
#include <vector>
#include "MatVec.h"

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>

template <unsigned DIM>
class Kugel {
	boost::units::quantity<boost::units::si::mass> m_mass; //mass ist nun ein Datentyp
	boost::units::quantity<boost::units::si::length> m_diameter;
public:
	MatVec<boost::units::quantity<boost::units::si::length>, DIM> vec_pos;
	MatVec<boost::units::quantity<boost::units::si::velocity>, DIM> vec_vel; //velocity ist nun ein Datentyp
	//collision next_collision;

	Kugel();
	Kugel(const Kugel<DIM> & kugel);
	Kugel(boost::units::quantity<boost::units::si::mass> m_mass,
			boost::units::quantity<boost::units::si::length> d);

	friend void swap(Kugel<DIM>& kugelA, Kugel<DIM>& kugelB) {
			swap(kugelA.vec_pos, kugelB.vec_pos); //swap von MatVec
			swap(kugelA.vec_vel, kugelB.vec_vel); //swap von MatVec
			std::swap(kugelA.mass, kugelB.mass);
			std::swap(kugelA.diameter, kugelB.diameter);
	}

	std::ostream& print(std::ostream & os = std::cout) const;


};


#include "Kugel.cpp"


