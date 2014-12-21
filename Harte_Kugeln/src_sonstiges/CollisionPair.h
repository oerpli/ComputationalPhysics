#ifndef UNIT_TESTS_COLLISIONPAIR_H_
#define UNIT_TESTS_COLLISIONPAIR_H_

#include "MetaKugel.h"
#include <boost/units/systems/si.hpp>

template<unsigned DIM>
class CollisionPair {
private:
	typedef boost::units::quantity< boost::units::si::time , double > time_type;

	MetaKugel<DIM> *p_kugel1, *p_kugel2;
	time_type dtime; //change to time_type
	bool collision;
public:

	CollisionPair() = delete;
	CollisionPair(MetaKugel<DIM>& kugel1, MetaKugel<DIM>& kugel2);
	CollisionPair(MetaKugel<DIM>& kugel1, MetaKugel<DIM>& kugel2, time_type dtime,
			bool collision);

	friend void swap (CollisionPair<DIM>& cp1, CollisionPair<DIM>& cp2) {
		std::swap(cp1.p_kugel1, cp2.p_kugel1);
		std::swap(cp1.p_kugel2, cp2.p_kugel2);
		swap(cp1.dtime, cp2.dtime); // sollte swap von time_type verwenden
		std::swap(cp1.collision, cp2.collision);

	}

	CollisionPair<DIM>& operator =(CollisionPair<DIM> other);

	// if other < this assign other to this
	CollisionPair<DIM>& operator <=(const CollisionPair<DIM>& other);

	void set_collision(MetaKugel<DIM>& other, const time_type& dt, bool b);
	void set_collision(const time_type& dt, bool b);

	auto collision_time() const -> decltype(dtime) {return dtime;}

	auto kugel1() const -> decltype(&p_kugel1) {return &p_kugel1;}
	auto kugel2() const -> decltype(&p_kugel2) {return &p_kugel2;}
	// Compares based on dtime
	bool operator <(const CollisionPair<DIM>& other) const;
	bool operator >(const CollisionPair<DIM>& other) const;

	bool equal(const CollisionPair<DIM>& other) const;

	//typecast to bool
	operator bool() const { return collision; }
};

#include "CollisionPair.tpp"

#endif /* UNIT_TESTS_COLLISIONPAIR_H_ */
