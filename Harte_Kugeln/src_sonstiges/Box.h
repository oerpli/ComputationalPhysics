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

template<typename Numeric>
Numeric min(Numeric a, Numeric b) {
	if (a < b) return a;
	return b;
}

template<unsigned DIM>
class Box {
	timeT m_time; //System Zeit
	std::vector<Kugel<DIM>> vec_kugel;
	MatVec<lengthT, DIM> vec_abmessung;
	CollisionPair<DIM> next_collision_pair;
	bool b_initiate_pos, b_initiate_vel;

	void wrap_one(Kugel<DIM>& kugel) {
		auto pos = kugel.position();
		pos -=  floor(pos/vec_abmessung) % vec_abmessung;
		kugel.position(pos);
	}

	MatVec<lengthT,DIM> rand_pos_vec() const {
		MatVec<dimlessT,DIM> vec_rand {};
		for (auto& el : vec_rand) el = Rand::real_uniform();
		return vec_abmessung % vec_rand;
	}

	bool init_pos_rand() {
		unsigned trys {10}, trys_inner {15};
		bool b_contact {};
		const auto iter_begin = vec_kugel.begin(), iter_end = vec_kugel.end();
		auto iter_first = vec_kugel.begin(), iter_second = vec_kugel.end();
		lengthT radius_first {};

		for (unsigned outer = 0; outer < trys; ++outer) {
			for (iter_first = iter_begin; iter_first != iter_end; ++iter_first) {
				for (unsigned inner = 0; inner < trys_inner; ++inner) {
					iter_first->position(rand_pos_vec());

					radius_first = iter_first->radius();
					b_contact = false;
					// überprüfe Kontakt mit Kugeln
					for(iter_second = iter_begin; iter_second != iter_first; ++iter_second) {
						if (dist(*iter_first, *iter_second).norm() <= radius_first + iter_second->radius()) {
							b_contact = true;
							break;
						}
					}
					if (! b_contact) break;
				}
				if (b_contact) break;
			}
			if (! b_contact) break;
		}
		return ! b_contact;
	}

	bool init_vel_rand() {
		const auto it_begin = vec_kugel.begin(), it_end = vec_kugel.end();
		auto first = it_begin;

		MatVec<velocityT,DIM> vec_sum{}, vel_buf{};

		for_each (++first, it_end, [&](Kugel<DIM>& k)->void {
			for (auto& el : vel_buf) el = Rand::real_uniform() * mps;
			k.velocity(vel_buf);
			vec_sum += vel_buf;
		} );
		it_begin->velocity(-vec_sum);

		energyT ekin{ };
		for_each (it_begin, it_end, [&](const Kugel<DIM>& k){ekin+=k.ekin();});
		dimlessT vel_scale = 1/sqrt( ekin / (N*m) );

		for_each (it_begin, it_end, [&](Kugel<DIM>& k){k.velocity(k.velocity()*vel_scale);});
		return true;
	}

	CollisionPair<DIM> calc_event(Kugel<DIM>& k1, Kugel<DIM>& k2) {
		CollisionPair<DIM> result = calc_collision_time(k1,k2) ;
		if (result) assert( result.collision_time() >= 0 * s);
		if (result) return result;
		timeT wall_t1 { calc_wall_collision_time(k1) };
		timeT wall_t2 { calc_wall_collision_time(k2) };
//		std::cout << "Wall_t1: " << wall_t1;
//		std::cout << "\tWall_t2: " << wall_t2 << std::endl;
		assert( wall_t1 >= 0 * s );
		assert( wall_t2 >= 0 * s );
		if (wall_t1 < wall_t2)	return CollisionPair<DIM>{k1, k2, wall_t1, false};
		return CollisionPair<DIM>{k1,k2, wall_t2, false};
	}

public:
	timeT time() const { return m_time; }

	void fast_forward(const timeT& dt) {
		if (dt == 0*s) return;
		m_time += dt;
		next_collision_pair.fast_forward(dt);
		for (auto& kugel : vec_kugel) {
			kugel.fast_forward(dt);
			wrap_one(kugel);
		}
	}

	void fast_forward() {
		return fast_forward (next_collision_pair.collision_time());
	}
	void wrap() {
		for (auto& kugel : vec_kugel) wrap_one(kugel);
	}

	Box(const MatVec<lengthT, DIM>& dim, unsigned size, const Kugel<DIM>& kugel)
		: m_time{},vec_kugel(size, kugel), vec_abmessung{dim}
		, next_collision_pair{vec_kugel[0], vec_kugel[0]}
		, b_initiate_pos{false}, b_initiate_vel{false} {}
	Box(const MatVec<lengthT, DIM>& dim, unsigned size)
		: m_time{}, vec_kugel(size), vec_abmessung{dim}
		, next_collision_pair{vec_kugel[0], vec_kugel[0]}
		, b_initiate_pos{false}, b_initiate_vel{false}  {}
	Box(const MatVec<lengthT, DIM>& dim)
			: Box{dim,0} {}


	bool initiate() {
		if (! b_initiate_pos) b_initiate_pos = init_pos_rand();
		if (! b_initiate_vel) b_initiate_vel = init_vel_rand();

		init_next_collision();
		return b_initiate_pos && b_initiate_vel;
	}

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
		b_initiate_pos = b_initiate_vel = false;
	}

	auto dist(const Kugel<DIM>& kugel1, const Kugel<DIM>& kugel2) const
			-> decltype(Kugel<DIM>{}.position()) { //TODO Ursprung links unten
		auto result = kugel2.position() - kugel1.position();
		result -= round(result/vec_abmessung) % vec_abmessung;
		return result;
	}

	void collide() {
		fast_forward();
		if(next_collision_pair)
			collide_cp(next_collision_pair);
		next_collision();
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
		auto it_start = vec_time.begin();
		std::for_each (++it_start, vec_time.end(), [&] (const timeT& time) {
			if (time < min_time) min_time = time; });
		return min_time;
	}

	CollisionPair<DIM> calc_collision_time(Kugel<DIM>& kugel_i, Kugel<DIM>& kugel_j) {
		MatVec<lengthT, DIM> rij { kugel_j.position() - kugel_i.position() };
		MatVec<velocityT, DIM> vij { kugel_j.velocity() - kugel_i.velocity() };

		auto b = rij * vij;
		if ( b >= 0*m*mps ) return CollisionPair<DIM>{kugel_i,kugel_j,0,false};
		auto d2 = Pow(kugel_i.radius()+kugel_j.radius(),2);
		auto r2 = rij.norm2();
		auto v2 = vij.norm2();

		auto sqr_sq = Pow(b,2) - v2 * ( r2 - d2 );
		if ( sqr_sq < 0 ) return CollisionPair<DIM>{kugel_i,kugel_j,0,false};

		auto q = - b + sqrt( sqr_sq );
		timeT coll_time { min( q / v2, ( r2 - d2 ) / q ) };
		return CollisionPair<DIM>{kugel_i, kugel_j, coll_time, true};
	}

	void init_next_collision() {
		const auto it_begin = vec_kugel.begin(), it_end = vec_kugel.end();
		auto first = it_begin, second = first;

		++second;
		next_collision_pair = set_collision(calc_event(*first, *second), *first, *second);
		for (++second; second != it_end; ++second)
			next_collision_pair <= set_collision_if(
					set_collision(calc_event(*first, *second), *second), *first);

		for (++first; first != it_end; ++first)
			for (second = first, ++second; second != it_end; ++second)
				next_collision_pair <= set_collision_if(
						calc_event(*first, *second), *first, *second);
	}

	void next_collision() {
		auto k1 = next_collision_pair.kugel1(), k2 = next_collision_pair.kugel2();

		next_collision_pair = set_collision(calc_event(k1,k2),k1,k2);
		for_each (vec_kugel.begin(), vec_kugel.end(), [&](Kugel<DIM>& k) {
			// Optimierung möglich, da wall_collision_time von k1 & k2 = const
			if (&k != &k1) next_collision_pair <= set_collision_if(calc_event(k,k1),k,k1);
			if (&k != &k2) next_collision_pair <= set_collision_if(calc_event(k,k2),k,k2);
		});
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

	std::ostream& print(std::ostream& os) const {
		for(const auto& kugel : vec_kugel) {
			kugel.print(os);
			os << '\n';
		}
		return os;
	}

	template<class UnitaryFunc>
	UnitaryFunc unitary(UnitaryFunc func) const {
		return for_each(vec_kugel.cbegin(), vec_kugel.cend(), func);
	}
};

template<unsigned DIM>
std::ostream& operator<< (std::ostream& os, const Box<DIM>& box) {
	box.print(os);
	return os;
}
#endif
