#ifndef KUGEL_H
#define KUGEL_H

#include <iostream>
#include <vector>
#include "MatVec.h"

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>


template <unsigned DIM>
class Kugel {
	typedef boost::units::quantity< boost::units::si::length , double > length_type;
	typedef boost::units::quantity< boost::units::si::velocity , double > velocity_type;
	typedef boost::units::quantity< boost::units::si::mass , double > mass_type;

	mass_type m_mass; //mass ist nun ein Datentyp
	length_type m_diameter;
public:
	MatVec<length_type, DIM> vec_pos;
	MatVec<velocity_type, DIM> vec_vel; //velocity ist nun ein Datentyp
	//collision next_collision;

	Kugel();
	Kugel(const Kugel<DIM> & kugel);
	Kugel(mass_type m_mass,
			length_type d);

	friend void swap(Kugel<DIM>& kugelA, Kugel<DIM>& kugelB) {
			swap(kugelA.vec_pos, kugelB.vec_pos); //swap von MatVec
			swap(kugelA.vec_vel, kugelB.vec_vel); //swap von MatVec
			swap(kugelA.m_mass, kugelB.m_mass); //units swap
			swap(kugelA.m_diameter, kugelB.m_diameter); //units swap
	}

	std::ostream& print(std::ostream & os = std::cout) const;


};


#include "Kugel.tpp"

#endif

