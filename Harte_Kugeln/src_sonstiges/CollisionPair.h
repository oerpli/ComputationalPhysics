#ifndef UNIT_TESTS_COLLISIONPAIR_H_
#define UNIT_TESTS_COLLISIONPAIR_H_

#include "MetaKugel.h"
#include "units_typedef.h"

template<unsigned DIM>
class CollisionPair {
private:
	typedef boost::units::quantity< boost::units::si::time , double > timeT;

	MetaKugel<DIM> *p_kugel1, *p_kugel2;
	timeT dtime; //change to timeT
	bool collision; // 0 für wall, 1 für kugel
public:

	CollisionPair() = delete;
	CollisionPair(MetaKugel<DIM>& kugel1, MetaKugel<DIM>& kugel2);
	CollisionPair(MetaKugel<DIM>& kugel1, MetaKugel<DIM>& kugel2, timeT dtime,
			bool collision);

	friend void swap (CollisionPair<DIM>& cp1, CollisionPair<DIM>& cp2) {
		std::swap(cp1.p_kugel1, cp2.p_kugel1);
		std::swap(cp1.p_kugel2, cp2.p_kugel2);
		swap(cp1.dtime, cp2.dtime); // sollte swap von timeT verwenden
		std::swap(cp1.collision, cp2.collision);

	}

	CollisionPair<DIM>& operator =(CollisionPair<DIM> other);

	// if other < this assign other to this
	CollisionPair<DIM>& operator <=(const CollisionPair<DIM>& other);

	void set_collision(MetaKugel<DIM>& first, MetaKugel<DIM>& other, const timeT& dt, bool b);
	void set_collision(MetaKugel<DIM>& other, const timeT& dt, bool b);
	void set_collision(const timeT& dt, bool b);
	void fast_forward(const timeT& dt);

	auto collision_time() const -> decltype(dtime) {return dtime;}

	auto kugel1() const -> decltype(p_kugel1) {return p_kugel1;}
	auto kugel2() const -> decltype(p_kugel2) {return p_kugel2;}
	// Compares based on dtime
	bool operator <(const CollisionPair<DIM>& other) const;
	bool operator >(const CollisionPair<DIM>& other) const;

	bool equal(const CollisionPair<DIM>& other) const;

	//typecast to bool
	operator bool() const { return collision; }
};

template<unsigned DIM>
void collide(const CollisionPair<DIM>& cp) {
	return collide(*cp.kugel1(), *cp.kugel2());
}

#include "CollisionPair.tpp"

#endif /* UNIT_TESTS_COLLISIONPAIR_H_ */
