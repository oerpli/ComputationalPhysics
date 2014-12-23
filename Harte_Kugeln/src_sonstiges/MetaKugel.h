#ifndef METAKUGEL_H
#define METAKUGEL_H

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
class MetaKugel {
	typedef boost::units::quantity< boost::units::si::length , double > length_type;
	typedef boost::units::quantity< boost::units::si::velocity , double > velocity_type;
	typedef boost::units::quantity< boost::units::si::mass , double > mass_type;
	typedef boost::units::quantity< boost::units::si::energy , double > energy_type;
	typedef boost::units::quantity< boost::units::si::time , double > time_type;

	mass_type m_mass; //mass ist nun ein Datentyp
	length_type m_radius;
	energy_type m_ekin;
	MatVec<velocity_type, DIM> vec_vel; //velocity ist nun ein Datentyp
	MatVec<length_type, DIM> vec_pos;


	void update_ekin();

public:
	//collision next_collision;

	MetaKugel();
	MetaKugel(const MetaKugel<DIM> & kugel);
	MetaKugel(mass_type m_mass,	length_type d);
	virtual ~MetaKugel() {};

	friend void swap(MetaKugel<DIM>& kugelA, MetaKugel<DIM>& kugelB) {
			swap(kugelA.vec_pos, kugelB.vec_pos); //swap von MatVec
			swap(kugelA.vec_vel, kugelB.vec_vel); //swap von MatVec
			swap(kugelA.m_mass, kugelB.m_mass); //units swap
			swap(kugelA.m_radius, kugelB.m_radius); //units swap
			swap(kugelA.m_ekin, kugelB.m_ekin);
	}

	virtual bool operator==(const MetaKugel<DIM>& other) const;

	auto radius() const -> decltype(m_radius) {return m_radius;}

	auto mass() const -> decltype(m_mass) {return m_mass;}

	void velocity(MatVec<velocity_type, DIM> vec);
	auto velocity() const -> decltype(vec_vel);

	void position(MatVec<length_type, DIM> vec);
	auto position() const -> decltype(vec_pos);

	auto ekin() const -> decltype(m_ekin);

	virtual void fast_forward(const time_type& dt);

	std::ostream& print(std::ostream & os = std::cout) const;


};

#include "MetaKugel.tpp"


template<unsigned DIM>
void collide(MetaKugel<DIM>& kugel1, MetaKugel<DIM>& kugel2) {
	const auto v1 = kugel1.velocity(), v2 = kugel2.velocity();
	const auto m1 = kugel1.mass(), m2 = kugel2.mass();

	const auto dist =  kugel2.position() - kugel1.position();
	const auto d = dist / dist.norm();

	const auto v_rel = ( d * (d * v2) - d * (d * v1) ) / ( 0.5 * (m1 + m2) );

	kugel1.velocity( v1 + ( v_rel * m2) );
	kugel2.velocity( v2 - ( v_rel * m1) );
}


template<unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MetaKugel<DIM>& kugel) {
	return kugel.print(os);
}

#endif // METAKUGEL_H

