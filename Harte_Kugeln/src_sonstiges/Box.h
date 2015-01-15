#ifndef BOX_H
#define BOX_H
#include <ostream>
#include <vector>
#include <algorithm>
#include "CollisionPair.h"
#include "MatVec.h"
#include "Kugel.h"
#include "Rand.h"

#include <cassert>

template<unsigned DIM>
class Box {
	timeT m_time; //System Zeit
	std::vector<Kugel<DIM>> vec_kugel;
	MatVec<lengthT, DIM> vec_abmessung;
	CollisionPair<DIM> next_collision_pair;
	bool b_initiate_pos, b_initiate_vel;


	//wrap for lvalue
	MatVec<lengthT,DIM>& wrap (MatVec<lengthT,DIM>& pos);
	//wrap for rvalue
	MatVec<lengthT,DIM> wrap (MatVec<lengthT,DIM>&& pos);

	void wrap_one(Kugel<DIM>& kugel);


	MatVec<lengthT,DIM> rand_pos_vec() const;

	bool check_no_touching() const;

	bool init_pos_rand();

	bool init_pos_lattice();

	bool check_ekin_1() const;

	bool init_vel_rand();

	void init_next_collision();

	void next_collision();


	CollisionPair<DIM> calc_event(Kugel<DIM>& k1, Kugel<DIM>& k2);


	void collide(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2);
	void collide(CollisionPair<DIM>& cp);


	timeT forward(MatVec<lengthT,DIM>& v_pos, const MatVec<velocityT,DIM>& v_vel,
			MatVec<timeT,DIM>& v_act_t,
			const MatVec<timeT,DIM>& v_res_t, const MatVec<lengthT,DIM>& v_res_p);

	auto dist(const Kugel<DIM>& kugel1, const Kugel<DIM>& kugel2) const;

public:
	timeT time() const;

	timeT fast_forward(const timeT& dt);
	timeT fast_forward();

	void wrap();

	Box() = delete;
	Box(const MatVec<lengthT, DIM>& dim, unsigned size, const Kugel<DIM>& kugel);
	Box(const MatVec<lengthT, DIM>& dim, unsigned size);
	Box(const MatVec<lengthT, DIM>& dim);


	const Kugel<DIM>& operator [](unsigned i) const;

	Kugel<DIM>& operator [](unsigned i);


	void add(const Box<DIM>& other);


	auto size() const;

	auto abmessung() const;


	bool initiate();

	timeT collide();


	timeT next_event() const;

	const CollisionPair<DIM>& collision_pair() const;


	template<class UnaryFunc, class BinaryFunc>
	void operator() (UnaryFunc& ufunc, BinaryFunc& bfunc) const;

	template<class UnitaryFunc>
	UnitaryFunc unitary(UnitaryFunc func) const;


	std::ostream& print(std::ostream& os) const;
};

template<unsigned DIM>
std::ostream& operator<< (std::ostream& os, const Box<DIM>& box);

#include "Box.tpp"

#endif
