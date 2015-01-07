#ifndef BOX_H
#define BOX_H
#include <ostream>
#include <vector>
#include <algorithm>
#include "CollisionPair.h"
#include "MatVec.h"
#include "Kugel.h"
#include "Rand.h"

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
		, next_collision_pair{vec_kugel[0], vec_kugel[0]}
		, b_initiate_pos{false} {}
	Box(const MatVec<lengthT, DIM>& dim, unsigned size)
		: m_time{}, vec_kugel(size), vec_abmessung{dim}
		, next_collision_pair{vec_kugel[0], vec_kugel[0]}
		, b_initiate_pos{false}  {}
	Box(const MatVec<lengthT, DIM>& dim)
			: Box{dim,0} {}


	bool initiate() {
		if (! b_initiate_pos) b_initiate_pos = init_pos_rand();
		if (! b_initiate_vel) b_initiate_vel = init_vel_rand();

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
		b_initiate_pos = false;
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

	timeT calc_collision_time(Kugel<DIM>& kugel_i, Kugel<DIM>& kugel_j) {
		MatVec<lengthT, DIM> rij { };
		MatVec<velocityT, DIM> vij { };
		rij = kugel_j.position() - kugel_i.position();
		vij = kugel_j.velocity() - kugel_i.velocity();
		timeT coll_time {100000*s};
		auto nullm2 = 0*m*mps;
		if ( rij*vij < nullm2 ) {
			auto coll_dist_sq = Pow(kugel_i.radius()+kugel_j.radius(),2);
			coll_time = (- rij * vij - sqrt((coll_dist_sq - rij*rij)*(vij*vij) + Pow(rij*vij,2)))/(vij*vij);
		}
		return coll_time;
	}

	void first_collision() {
		timeT temp_coll_time {10000*s}; //arbitrary, irgendwas großes halt
		next_collision_pair.set_collision(temp_coll_time, 0);
		for (unsigned i = 0; i < vec_kugel.size(); i++) {
			temp_coll_time = calc_wall_collision_time(vec_kugel[i]);
			if (temp_coll_time < next_collision_pair.collision_time()) {
				next_collision_pair.set_collision(temp_coll_time, 0);
			}
			for (unsigned j = i + 1; j < vec_kugel.size(); j++) {
				temp_coll_time = calc_collision_time(vec_kugel[i], vec_kugel[j]);
				if (temp_coll_time < vec_kugel[i].collision_time()) {
					vec_kugel[i].set_collision(vec_kugel[j], temp_coll_time, 1);
				}
				if (temp_coll_time < vec_kugel[j].collision_time()) {
					vec_kugel[j].set_collision(vec_kugel[i], temp_coll_time, 1);
				}
				if (temp_coll_time < next_collision_pair.collision_time()) {
					next_collision_pair.set_collision(vec_kugel[i], vec_kugel[j], temp_coll_time, 1);
				}
			}
		}
		fast_forward(next_collision_pair.collision_time());
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

	std::ostream& print(std::ostream& os) const {
		for(const auto& kugel : vec_kugel) {
			kugel.print(os);
			os << '\n';
		}
		return os;
	}
};

template<unsigned DIM>
std::ostream& operator<< (std::ostream& os, const Box<DIM>& box) {
	box.print(os);
	return os;
}
#endif
