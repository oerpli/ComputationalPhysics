#ifndef KUGEL_H
#define KUGEL_H

#include <iostream>
#include <vector>
#include "MatVec.h"

#include <boost/units/cmath.hpp>
#include <boost/units/pow.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>
#include <boost/units/derived_dimension.hpp>

#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/physical_dimensions/mass.hpp>
#include <boost/units/physical_dimensions/time.hpp>

using namespace boost::units;
using namespace boost::units::si;

template <unsigned DIM>
class Kugel {
	typedef boost::units::quantity< boost::units::si::length , double > length_type;
	typedef boost::units::quantity< boost::units::si::velocity , double > velocity_type;
	typedef boost::units::quantity< boost::units::si::mass , double > mass_type;
	typedef boost::units::quantity< boost::units::si::energy , double > energy_type;

	mass_type m_mass; //mass ist nun ein Datentyp
	length_type m_diameter;
	energy_type m_ekin;
	MatVec<velocity_type, DIM> vec_vel; //velocity ist nun ein Datentyp

	void update_ekin();

public:
	MatVec<length_type, DIM> vec_pos;
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
			swap(kugelA.m_ekin, kugelB.m_ekin);
	}

	auto radius() const -> decltype(m_diameter) {return m_diameter * 0.5;}

	auto mass() const -> decltype(m_mass) {return m_mass;}

	void velocity(MatVec<velocity_type, DIM> vec);
	auto velocity() const -> decltype(vec_vel);

	auto ekin() const -> decltype(m_ekin);

	std::ostream& print(std::ostream & os = std::cout) const;


};

#include "Kugel.tpp"


template<unsigned DIM>
void collide(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2) {
	const auto dist =  kugel2.vec_pos - kugel1.vec_pos;
	const auto d = dist / dist.norm();

	const auto v1 = kugel1.velocity(), v2 = kugel2.velocity();
	const auto m1 = kugel1.mass(), m2 = kugel2.mass();

	const auto v_rel = ( d * (d * v2) - d * (d * v1) ) / ( 0.5 * (m1 + m2) );

	kugel1.velocity( v1 + ( v_rel * m2) );
	kugel2.velocity( v2 - ( v_rel * m1) );
}

template<unsigned DIM>
std::ostream& operator<< (std::ostream& os, const Kugel<DIM>& kugel) {
	return kugel.print(os);
}
#endif

