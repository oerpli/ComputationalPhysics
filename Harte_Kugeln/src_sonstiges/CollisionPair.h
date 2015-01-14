#ifndef UNIT_TESTS_COLLISIONPAIR_H_
#define UNIT_TESTS_COLLISIONPAIR_H_

#include <utility>

#include "Kugel.h"
#include "units_typedef.h"

template<unsigned DIM>
class CollisionPair {
private:
	Kugel<DIM> *p_kugel1, *p_kugel2;
	timeT dtime; //change to timeT
	bool collision; // 0 für wall, 1 für kugel
public:

	CollisionPair() = default;
	CollisionPair(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2, timeT dtime,
			bool collision);
	explicit CollisionPair(Kugel<DIM>& k) : p_kugel1{&k}, p_kugel2{k.collision_partner()},
			dtime{k.collision_time()}, collision{k.collision_bool()} {}
	~CollisionPair() = default;

	CollisionPair(const CollisionPair& other) = default;
	CollisionPair(CollisionPair&& other) = default;

	CollisionPair& operator =(const CollisionPair& other) = default;
	CollisionPair& operator =(CollisionPair&& other) = default;

	CollisionPair<DIM>& operator =(Kugel<DIM>& k);

	// if other.dtime < this->dtime assign other to this
	// perfect forwarding to operator=
	template<class OtherCollisionPair>
	CollisionPair<DIM>& operator <=(OtherCollisionPair&& other);
	CollisionPair<DIM>& operator <=(Kugel<DIM>& k);

	friend void swap (CollisionPair<DIM>& cp1, CollisionPair<DIM>& cp2) {
		std::swap(cp1.p_kugel1, cp2.p_kugel1);
		std::swap(cp1.p_kugel2, cp2.p_kugel2);
		std::swap(cp1.dtime, cp2.dtime); // sollte swap von timeT verwenden
		std::swap(cp1.collision, cp2.collision);

	}

	bool operator ==(const CollisionPair<DIM> other);

	// Compares based on dtime
	bool operator <(const CollisionPair<DIM>& other) const;
	bool operator >(const CollisionPair<DIM>& other) const;


	void set_collision(Kugel<DIM>& first, Kugel<DIM>& other, const timeT& dt, bool b);
	void fast_forward(const timeT& dt);


	Kugel<DIM>& kugel1();
	const Kugel<DIM>& kugel1() const;

	Kugel<DIM>& kugel2();
	const Kugel<DIM>& kugel2() const;

	timeT collision_time() const;

	//typecast to bool
	explicit operator bool() const;
};

template<unsigned DIM>
CollisionPair<DIM> set_collision(CollisionPair<DIM> cp, Kugel<DIM>& k);
template<unsigned DIM>
CollisionPair<DIM> set_collision(CollisionPair<DIM> cp, Kugel<DIM>& k1, Kugel<DIM>& k2);

template<unsigned DIM>
CollisionPair<DIM> set_collision_if(CollisionPair<DIM> cp, Kugel<DIM>& k);
template<unsigned DIM>
CollisionPair<DIM> set_collision_if(CollisionPair<DIM> cp, Kugel<DIM>& k1,
		Kugel<DIM>& k2);

#include "CollisionPair.tpp"

#endif /* UNIT_TESTS_COLLISIONPAIR_H_ */
