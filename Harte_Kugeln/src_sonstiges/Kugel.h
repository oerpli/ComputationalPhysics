#ifndef KUGEL_H
#define KUGEL_H

#include <iostream>
#include <vector>

#include "MatVec.h"
#include "units_typedef.h"

template<unsigned DIM>
class Kugel {
private:
	massT m_mass; //mass ist nun ein Datentyp
	lengthT m_radius;
	energyT m_ekin;
	MatVec<velocityT, DIM> vec_vel; //velocity ist nun ein Datentyp
	MatVec<lengthT, DIM> vec_pos;

	Kugel<DIM> *m_p_partner;
	timeT m_t_collision;
	bool m_b_collision;

	void update_ekin();
public:
	Kugel() = default;
	Kugel(const Kugel& other) = default;
	Kugel(Kugel&& other) = default;
	Kugel(massT mass,	lengthT d);
	~Kugel() = default;

	Kugel& operator =(const Kugel& other) = default;
	Kugel& operator =(Kugel&& other) = default;

	friend void swap(Kugel<DIM>& kugelA, Kugel<DIM>& kugelB) {
			std::swap(kugelA.m_p_partner, kugelB.m_p_partner);
			swap(kugelA.m_t_collision, kugelB.m_t_collision);
			std::swap(kugelA.m_b_collision, kugelB.m_b_collision);
			swap(kugelA.vec_pos, kugelB.vec_pos); //swap von MatVec
			swap(kugelA.vec_vel, kugelB.vec_vel); //swap von MatVec
			swap(kugelA.m_mass, kugelB.m_mass); //units swap
			swap(kugelA.m_radius, kugelB.m_radius); //units swap
			swap(kugelA.m_ekin, kugelB.m_ekin);
	}

	bool operator==(const Kugel<DIM>& other) const;

	auto radius() const -> decltype(m_radius) {return m_radius;}

	auto mass() const -> decltype(m_mass) {return m_mass;}

	void velocity(MatVec<velocityT, DIM> vec);
	auto velocity() const -> decltype(vec_vel);

	void position(MatVec<lengthT, DIM> vec);
	auto position() const -> decltype(vec_pos);

	auto ekin() const -> decltype(m_ekin);

	void fast_forward(const timeT& dt);

	timeT collision_time() const;
	bool collision_bool() const {return m_b_collision;}
	Kugel<DIM>* collision_partner() const {return m_p_partner;}

	void set_collision(Kugel<DIM>& other, const timeT& dt, bool b);

	std::ostream& print(std::ostream & os = std::cout) const;
};

template<unsigned DIM>
std::ostream& operator<< (std::ostream& os, const Kugel<DIM>& kugel) {
	return kugel.print(os);
}

#include "Kugel.tpp"

#endif // KUGEL_H
