#ifndef METAKUGEL_H
#define METAKUGEL_H

#include <iostream>
#include <vector>
#include "MatVec.h"

#include "units_typedef.h"

template <unsigned DIM>
class MetaKugel {

	massT m_mass; //mass ist nun ein Datentyp
	lengthT m_radius;
	energyT m_ekin;
	MatVec<velocityT, DIM> vec_vel; //velocity ist nun ein Datentyp
	MatVec<lengthT, DIM> vec_pos;


	void update_ekin();

public:
	//collision next_collision;

	MetaKugel();
	MetaKugel(const MetaKugel<DIM> & kugel);
	MetaKugel(massT m_mass,	lengthT d);
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

	void velocity(MatVec<velocityT, DIM> vec);
	auto velocity() const -> decltype(vec_vel);

	void position(MatVec<lengthT, DIM> vec);
	auto position() const -> decltype(vec_pos);

	auto ekin() const -> decltype(m_ekin);

	virtual void fast_forward(const timeT& dt);

	std::ostream& print(std::ostream & os = std::cout) const;


};

#include "MetaKugel.tpp"

template<unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MetaKugel<DIM>& kugel) {
	return kugel.print(os);
}

#endif // METAKUGEL_H

