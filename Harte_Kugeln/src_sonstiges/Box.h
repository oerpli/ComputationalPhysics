#ifndef BOX_H
#define BOX_H
#include <vector>
#include <algorithm>
#include "CollisionPair.h"
#include "MatVec.h"
#include "Kugel.h"

template<unsigned DIM>
class Box {
	timeT m_time; //System Zeit
	std::vector<Kugel<DIM>> vec_kugel;
	MatVec<lengthT, DIM> vec_abmessung;
	CollisionPair<DIM> next_collision_pair;

	void wrap_one(Kugel<DIM>& kugel) {
		auto pos = kugel.position();
		pos -=  floor(pos/vec_abmessung) % vec_abmessung;
		kugel.position(pos);
	}

	CollisionPair<DIM> calc_event(Kugel<DIM>& k1, Kugel<DIM>& k2) {
		CollisionPair<DIM> result { calc_collision_time(k1,k2) };
		if (result) return result;
		timeT wall_t1 { calc_wall_collision_time(k1) };
		timeT wall_t2 { calc_wall_collision_time(k2) };
		if (wall_t1 < wall_t2)	return CollisionPair<DIM>{k1, k2, wall_t1, false};
		return CollisionPair<DIM>{k1,k2, wall_t2, false};
	}

public:
	timeT time() const { return m_time; }

	void fast_forward(const timeT& dt) {
		m_time += dt;
		for (auto& kugel : vec_kugel) {
			kugel.fast_forward(dt);
			wrap_one(kugel);
		}
		if (next_collision_pair)
			collide(next_collision_pair);
	}

	void wrap() {
		for (auto& kugel : vec_kugel) wrap_one(kugel);
	}

	Box(const MatVec<lengthT, DIM>& dim, unsigned size, const Kugel<DIM>& kugel)
		: m_time{},vec_kugel(size, kugel), vec_abmessung{dim}
		, next_collision_pair{vec_kugel[0], vec_kugel[0]} {}
	Box(const MatVec<lengthT, DIM>& dim, unsigned size)
		: m_time{}, vec_kugel(size), vec_abmessung{dim}
		, next_collision_pair{vec_kugel[0], vec_kugel[0]} {}
	Box(const MatVec<lengthT, DIM>& dim)
			: Box{dim,0} {}


	const Kugel<DIM>& operator [](unsigned i) const {
		return vec_kugel[i];
	}

	Kugel<DIM>& operator [](unsigned i) {
		return vec_kugel[i];
	}

	auto size() const -> decltype( vec_kugel.size() ){
		return vec_kugel.size();
	}

	auto abmessung() const -> decltype( vec_abmessung ) {
		return vec_abmessung;
	}

	void add(const Box<DIM>& other) {
		if ( vec_abmessung != other.vec_abmessung )
			return;
		vec_kugel.insert(vec_kugel.end(),
				other.vec_kugel.begin(), other.vec_kugel.end() );
	}

	auto dist(const Kugel<DIM>& kugel1, const Kugel<DIM>& kugel2) const
			-> decltype(Kugel<DIM>{}.position()) { //TODO Ursprung links unten
		auto result = kugel2.position() - kugel1.position();
		result -= round(result/vec_abmessung) % vec_abmessung;
		return result;
	}

	timeT calc_wall_collision_time(const Kugel<DIM>& kugel) {
		auto vel = kugel.velocity();
		MatVec<lengthT, DIM> border{};
		velocityT null{};

		for (unsigned i = 0; i < DIM; ++i)
			if ( vel[i] > null )
				border[i] = vec_abmessung[i];
		MatVec<timeT, DIM> vec_time = ( border - kugel.position() ) / vel;

		auto min_time = vec_time[0];
		for_each (++vec_time.begin(), vec_time.end(), [&] (const timeT& time) {
			if (time < min_time) min_time = time; });
		return min_time;
	}

	CollisionPair<DIM> calc_collision_time(Kugel<DIM>& kugel_i, Kugel<DIM>& kugel_j) {
		MatVec<lengthT, DIM> rij { kugel_j.position() - kugel_i.position() };
		MatVec<velocityT, DIM> vij { kugel_j.velocity() - kugel_i.velocity() };

		if ( rij*vij >= 0*m*mps ) return CollisionPair<DIM>{kugel_i,kugel_j,0,false};
		auto coll_dist_sq = Pow(kugel_i.radius()+kugel_j.radius(),2);
		auto coll_time = (- rij * vij - sqrt((coll_dist_sq - rij*rij)*(vij*vij) + Pow(rij*vij,2)))/(vij*vij);

		return CollisionPair<DIM>{kugel_i, kugel_j, coll_time, true};
	}

	void init_next_collision() {
		const auto it_begin = vec_kugel.begin(), it_end = vec_kugel.end();
		auto first = it_begin, second = first;

		next_collision_pair = calc_event(*first, *second);
		for (; first != it_end; ++first)
			for (second = first, ++second; second != it_end; ++second)
				next_collision_pair <= calc_event(*first, *second);
	}

	void next_collision() {
		timeT temp_coll_time {10000*s}; //arbitrary, irgendwas großes halt
		next_collision_pair.set_collision(temp_coll_time, 0);
		auto& kugel_i = *(next_collision_pair.kugel1());
		for (auto& kugel_j : vec_kugel) {
			if (kugel_i != kugel_j) { // stimmt das so? gedacht ist, zu schauen, ob *kugel_i und *kugel_j auf die gleiche adresse verweisen.
				temp_coll_time = calc_collision_time(kugel_i, kugel_j);
				if (temp_coll_time < kugel_i->collision_time()) {
				kugel_i.set_collision(kugel_j, temp_coll_time, 1);
				}
				if (temp_coll_time < kugel_j.collision_time()) {
				kugel_j.set_collision(kugel_i, temp_coll_time, 1);
				}
				if (temp_coll_time < next_collision_pair.collision_time()) {
				next_collision_pair.set_collision(kugel_i, kugel_j, temp_coll_time, 1);
				}
			}
		}
		kugel_i = *(next_collision_pair.kugel2());
		for (auto& kugel_j : vec_kugel) {
			if (kugel_i != kugel_j) {
				temp_coll_time = calc_collision_time(kugel_i, kugel_j);
				if (temp_coll_time < kugel_i.collision_time()) {
					kugel_i.set_collision(kugel_j, temp_coll_time, 1);
				}
				if (temp_coll_time < kugel_j.collision_time()) {
					kugel_j.set_collision(kugel_i, temp_coll_time, 1);
				}
				if (temp_coll_time < next_collision_pair.collision_time()) {
					next_collision_pair.set_collision(kugel_i, kugel_j, temp_coll_time, 0);
				}
				if (kugel_j.collision_time() < next_collision_pair.collision_time()) {
					next_collision_pair = kugel_j.collision_pair();
				}
			}
		}
		// TODO: next_collision_pair updaten... m_cp is ja private, also brauchen wir unter umständen noch einen getter
	}

	template<class UnaryFunc, class BinaryFunc>
	void operator() (UnaryFunc& ufunc, BinaryFunc& bfunc) const {
		auto first = vec_kugel.cbegin(), last = vec_kugel.cend();
		auto second = first;

		for(; first != last; ++first) {
			ufunc( *first );
			for( second = first + 1; second != last; ++second )
				bfunc( *first, *second );
		}
	}

};
#endif
