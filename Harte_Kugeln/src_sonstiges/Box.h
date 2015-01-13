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
	MatVec<lengthT,DIM>& wrap (MatVec<lengthT,DIM>& pos) {
		return pos -=  floor(pos/vec_abmessung) % vec_abmessung;
	}

	//wrap for rvalue
	MatVec<lengthT,DIM> wrap (MatVec<lengthT,DIM>&& pos) {
		return pos -=  floor(pos/vec_abmessung) % vec_abmessung;
	}

	void wrap_one(Kugel<DIM>& kugel) {
		kugel.position( wrap( kugel.position() ) );
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
		dimlessT vel_scale = 1/sqrt( .1 * (ekin / (N*m)) );

		for_each (it_begin, it_end, [&](Kugel<DIM>& k){k.velocity(k.velocity()*vel_scale);});
		return true;
	}

	timeT forward(MatVec<lengthT,DIM>& v_pos, const MatVec<velocityT,DIM>& v_vel,
			MatVec<timeT,DIM>& v_act_t,
			const MatVec<timeT,DIM>& v_res_t, const MatVec<lengthT,DIM>& v_res_p) {
		unsigned i_min{};
		timeT t_min{v_act_t[i_min]};

		for(unsigned i = 0; i < DIM; ++i) {
			if (v_act_t[i] < t_min) {
				t_min = v_act_t[i];
				i_min = i;
			}
		}
		v_act_t -= t_min;
		v_pos += v_vel * t_min;

		v_act_t[i_min] = v_res_t[i_min];
		v_pos[i_min] = v_res_p[i_min];
		return t_min;
	}

	CollisionPair<DIM> calc_event(Kugel<DIM>& k1, Kugel<DIM>& k2) {
		const unsigned versuche{ 7 };
		bool collision{false};
		timeT t_ges{};

		const MatVec<velocityT,DIM> v { k1.velocity() - k2.velocity() };
		const auto v2 = v.norm2();
		if (v2 == 0 *mps*mps)
			return CollisionPair<DIM>(k1, k2, std::numeric_limits<timeT>::max(), false);

		MatVec<timeT,DIM> v_res_t { vec_abmessung / v };
		v_res_t([&](timeT& t) {if (t < 0*s) t = -t;});
		MatVec<timeT,DIM> v_act_t{ };
		const MatVec<lengthT,DIM> pos_2 { vec_abmessung / dimlessT{2} };

		MatVec<lengthT,DIM> pos { wrap( pos_2 + k1.position() - k2.position() ) };

		MatVec<lengthT,DIM> v_res_pos{ };
		for (unsigned i = 0; i < DIM; ++i) {
			if (v[i] < 0 * mps) {
				v_res_pos[i] = vec_abmessung[i];
				v_act_t[i] = -(pos[i] / v[i]);
			}
			else
				v_act_t[i] = (vec_abmessung[i] - pos[i]) / v[i];
		}

		const auto d2 = Pow(k1.radius() + k2.radius(), 2);
		const auto d2v2 = d2 * v2;

		MatVec<lengthT,DIM> r {};
		auto rv = 0. *m *mps;
		const auto rv0 = 0. *m *mps;
		auto sr2 = 0. *m*m *mps*mps;
		const auto sr20 = 0. *m*m *mps*mps;

		for (unsigned i = 0; i < versuche; t_ges += forward(
				pos, v, v_act_t, v_res_t, v_res_pos), ++i) {
			r = pos - pos_2;
			rv = r * v;
			if (rv >= rv0) continue;
			sr2 = d2v2 - r.norm2() * v2 + Pow(rv,2);
			if (sr2 < sr20) continue;
			t_ges += -(rv + sqrt(sr2))/v2;
			collision = true;
			break;
		}
		return CollisionPair<DIM>{k1,k2, t_ges, collision};
	}

	void collide(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2) {
		const auto v1 = kugel1.velocity(), v2 = kugel2.velocity();
		const auto m1 = kugel1.mass(), m2 = kugel2.mass();

		const auto dis =  dist( kugel1, kugel2 );
		const auto n = dis / dis.norm();

		const auto p = -( n * (n * (v2 - v1) ) ) * ( dimlessT{2} * m1 * m2 / (m1 + m2) );

		kugel1.velocity( v1 - ( p / m1) );
		kugel2.velocity( v2 + ( p / m2) );
	}

	void collide(CollisionPair<DIM>& cp) {
		return collide(cp.kugel1(), cp.kugel2());
	}

public:
	timeT time() const { return m_time; }

	timeT fast_forward(const timeT& dt) {
		if (dt == 0*s) return 0*s;
		m_time += dt;
		next_collision_pair.fast_forward(dt);
		for (auto& kugel : vec_kugel) {
			kugel.fast_forward(dt);
			wrap_one(kugel);
		}
		return dt;
	}

	timeT fast_forward() {
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

	bool check_no_touching() const {
		auto k1 = vec_kugel.cbegin(), last = vec_kugel.cend();
		auto k2 = k1;

		for(; k1 != last; ++k1)
			for( k2 = k1 + 1; k2 != last; ++k2 )
				if ( dist( *k1, *k2 ).norm() < k1->radius() + k2->radius() )
					return false;
		return true;
	}

	bool check_ekin_1() const {
		energyT av{ };
		for (auto &el : vec_kugel) av += el.ekin();
		return av / (dimlessT)vec_kugel.size() == 1 *N*m;
	}

	bool initiate() {
		if (! b_initiate_pos) b_initiate_pos = check_no_touching();
		if (! b_initiate_pos) b_initiate_pos = init_pos_rand();
		if (! b_initiate_vel) b_initiate_vel = check_ekin_1();
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

	timeT collide() {
		timeT ret { fast_forward() };
		if(next_collision_pair)
			collide(next_collision_pair);
		next_collision();
		return ret;
	}

	timeT next_event() const {return next_collision_pair.collision_time() ;}

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
		auto &k1 = next_collision_pair.kugel1(), &k2 = next_collision_pair.kugel2();

		next_collision_pair = set_collision(calc_event(k1,k2),k1,k2);
		for_each (vec_kugel.begin(), vec_kugel.end(), [&](Kugel<DIM>& k) {
			if (&k != &k1 && &k != &k2) {
				set_collision_if(calc_event(k,k1),k,k1);
				set_collision_if(calc_event(k,k2),k,k2);
			}
			next_collision_pair <= k;
		});
		next_collision_pair <= k1;
		next_collision_pair <= k2;
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
