#ifndef UNIT_TESTS_COLLISIONPAIR_H_
#define UNIT_TESTS_COLLISIONPAIR_H_

#include "Kugel.h"
#include "units_typedef.h"

template<unsigned DIM>
class CollisionPair {
private:
	Kugel<DIM> *p_kugel1, *p_kugel2;
	timeT dtime; //change to timeT
	bool collision; // 0 für wall, 1 für kugel
public:

	CollisionPair() = delete;
	CollisionPair(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2);
	CollisionPair(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2, timeT dtime,
			bool collision);

	friend void swap (CollisionPair<DIM>& cp1, CollisionPair<DIM>& cp2) {
		std::swap(cp1.p_kugel1, cp2.p_kugel1);
		std::swap(cp1.p_kugel2, cp2.p_kugel2);
		std::swap(cp1.dtime, cp2.dtime); // sollte swap von timeT verwenden
		std::swap(cp1.collision, cp2.collision);

	}

	CollisionPair<DIM>& operator =(CollisionPair<DIM> other);

	// if other < this assign other to this
	CollisionPair<DIM>& operator <=(const CollisionPair<DIM>& other);

	void set_collision(Kugel<DIM>& first, Kugel<DIM>& other, const timeT& dt, bool b);
	void set_collision(Kugel<DIM>& other, const timeT& dt, bool b);
	void set_collision(const timeT& dt, bool b);
	void fast_forward(const timeT& dt);

	auto collision_time() const -> decltype(dtime) {return dtime;}

	Kugel<DIM>& kugel1() {return *p_kugel1;}
	Kugel<DIM>& kugel2() {return *p_kugel2;}

	const Kugel<DIM>& kugel1() const {return *p_kugel1;}
	const Kugel<DIM>& kugel2() const {return *p_kugel2;}
	// Compares based on dtime
	bool operator <(const CollisionPair<DIM>& other) const;
	bool operator >(const CollisionPair<DIM>& other) const;

	bool equal(const CollisionPair<DIM>& other) const;

	//typecast to bool
	operator bool() const { return collision; }
};

template<unsigned DIM>
void collide( CollisionPair<DIM>& cp);

template<unsigned DIM>
CollisionPair<DIM> set_collision(CollisionPair<DIM> cp, Kugel<DIM>& k);
template<unsigned DIM>
CollisionPair<DIM> set_collision(CollisionPair<DIM> cp, Kugel<DIM>& k1, Kugel<DIM>& k2);

template<unsigned DIM>
CollisionPair<DIM> set_collision_if(CollisionPair<DIM> cp, Kugel<DIM>& k);
template<unsigned DIM>
CollisionPair<DIM> set_collision_if(CollisionPair<DIM> cp, Kugel<DIM>& k1, Kugel<DIM>& k2);

#include "CollisionPair.tpp"

#endif /* UNIT_TESTS_COLLISIONPAIR_H_ */
