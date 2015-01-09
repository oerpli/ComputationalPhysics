#ifndef KUGEL_H
#define KUGEL_H


#include "MetaKugel.h"

template<unsigned DIM>
class Kugel : public MetaKugel<DIM> {
private:
	Kugel<DIM> *m_p_partner;
	timeT m_t_collision;
	bool m_b_collision;

public:
	Kugel();
	Kugel(const Kugel& other);
	Kugel(massT mass,	lengthT d);

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

	void fast_forward(const timeT& dt);

	timeT collision_time() const;

	void set_collision(Kugel<DIM>& other, const timeT& dt, bool b);
};

#include "Kugel.tpp"

#endif // KUGEL_H
