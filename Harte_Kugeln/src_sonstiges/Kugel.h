#ifndef KUGEL_H
#define KUGEL_H


#include "MetaKugel.h"
#include "CollisionPair.h"

template<unsigned DIM>
class Kugel : public MetaKugel<DIM> {
private:
	CollisionPair<DIM> m_cp;

public:
	Kugel();
	Kugel(const Kugel& other);
	Kugel(massT mass,	lengthT d);

	friend void swap(Kugel<DIM>& kugelA, Kugel<DIM>& kugelB) {
			swap(kugelA.vec_pos, kugelB.vec_pos); //swap von MatVec
			swap(kugelA.vec_vel, kugelB.vec_vel); //swap von MatVec
			swap(kugelA.m_mass, kugelB.m_mass); //units swap
			swap(kugelA.m_radius, kugelB.m_radius); //units swap
			swap(kugelA.m_ekin, kugelB.m_ekin);
			std::swap(kugelA.m_cp, kugelB.m_cp);
	}

	bool operator==(const Kugel<DIM>& other) const;

	void fast_forward(const timeT& dt);

	auto collision_time() const -> decltype(m_cp.collision_time());

	auto collision_pair() const -> decltype(m_cp);

	void set_collision(Kugel<DIM>& other, const timeT& dt, bool b);
};

#include "Kugel.tpp"

#endif // KUGEL_H
