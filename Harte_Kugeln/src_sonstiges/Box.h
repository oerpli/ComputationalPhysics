#ifndef BOX_H
#define BOX_H
#include <vector>
#include <algorithm>
#include "CollisionPair.h"
#include "MatVec.h"
#include "Kugel.h"

template<unsigned DIM>
class Box {
	typedef boost::units::quantity< boost::units::si::length , double > lengthT;
	typedef boost::units::quantity< boost::units::si::velocity , double > velocityT;
	typedef boost::units::quantity< boost::units::si::mass , double > massT;
	typedef boost::units::quantity< boost::units::si::energy , double > energyT;
	typedef boost::units::quantity< boost::units::si::time , double > timeT;
	typedef boost::units::quantity< boost::units::si::dimensionless , int > idimlessT;

	timeT m_time; //System Zeit
	std::vector<Kugel<DIM>> vec_kugel;
	MatVec<lengthT, DIM> vec_abmessung;
	CollisionPair<DIM> next_collision_pair;

	void wrap_one(Kugel<DIM>& kugel) {
		auto pos = kugel.position();
		pos -=  floor(pos/vec_abmessung) % vec_abmessung;
		kugel.position(pos);
	}

public:
	timeT time() const { return m_time; }

	void fast_forward(const timeT& dt) {
		m_time += dt;
		for (auto& kugel : vec_kugel) {
			kugel.fast_forward(dt);
			wrap_one(kugel);
		}
		if (bool(next_collision_pair)) {
			Kugel<DIM> *kugel_i = static_cast<Kugel<DIM>*>(next_collision_pair.kugel1());
			Kugel<DIM> *kugel_j = static_cast<Kugel<DIM>*>(next_collision_pair.kugel2());
			collide(*kugel_i,*kugel_j);
		}
	}

	void collide(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2) {
		std::cout << "blubb" << std::endl;
		const auto v1 = kugel1.velocity(), v2 = kugel2.velocity();
		const auto m1 = kugel1.mass(), m2 = kugel2.mass();

		const auto dist =  kugel2.position() - kugel1.position();
		const auto d = dist / dist.norm();

		const auto v_rel = ( d * (d * v2) - d * (d * v1) ) / ( 0.5 * (m1 + m2) );

		kugel1.velocity( v1 + ( v_rel * m2) );
		kugel2.velocity( v2 - ( v_rel * m1) );
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

	timeT calc_collision_time(Kugel<DIM>& kugel_i, Kugel<DIM>& kugel_j) {
		MatVec<lengthT, DIM> rij { };
		MatVec<velocityT, DIM> vij { };
		rij = kugel_j.position() - kugel_i.position();
		vij = kugel_j.velocity() - kugel_i.velocity();
		timeT coll_time {100000*second};
		auto nullm2 = 0*meter*meter/second;
		if ( rij*vij < nullm2 ) {
			auto coll_dist_sq = pow<2>(kugel_i.radius()+kugel_j.radius());
			coll_time = (- rij * vij - sqrt((coll_dist_sq - rij*rij)*(vij*vij) + pow<2>(rij*vij)))/(vij*vij);
		}
		return coll_time;
	}

	void first_collision() {
		timeT temp_coll_time {10000*second}; //arbitrary, irgendwas großes halt
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
		timeT temp_coll_time {10000*second}; //arbitrary, irgendwas großes halt
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

};
#endif
