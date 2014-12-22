#ifndef BOX_H
#define BOX_H
#include <vector>
#include <algorithm>
#include "Kugel.h"
#include "CollisionPair.h"
#include "MatVec.h"

template<unsigned DIM>
class Box {
	typedef boost::units::quantity< boost::units::si::length , double > lengthT;
	typedef boost::units::quantity< boost::units::si::velocity , double > velocityT;
	typedef boost::units::quantity< boost::units::si::mass , double > massT;
	typedef boost::units::quantity< boost::units::si::energy , double > energyT;
	typedef boost::units::quantity< boost::units::si::time , double > timeT;
	typedef boost::units::quantity< boost::units::si::dimensionless , int > idimlessT;

	timeT m_time;
	std::vector<Kugel<DIM>> vec_kugel;
	MatVec<lengthT, DIM> vec_abmessung;
	CollisionPair<DIM> next_collision_pair;

	void wrap_one(Kugel<DIM>& kugel) { //TODO Ursprung links unten
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

	void calc_collision_time(Kugel<DIM>& kugel_i, Kugel<DIM>& kugel_j) {
		MatVec<lengthT, DIM> rij { };
		MatVec<lengthT, DIM> vij { };
		rij = kugel_j.position() - kugel_i.position();
		vij = kugel_j.velocity() - kugel_i.velocity();
		timeT coll_time { };
		if ( rij*vij < 0.0 ) {
			auto coll_dist_sq = pow(2.0*(kugel_i.radius()+kugel_j.radius()),2);
			coll_time = (- rij * vij - sqrt((coll_dist_sq - rij*rij)*(vij*vij) + pow(rij*vij,2)))/(vij*vij);
			if (coll_time < kugel_i.collision_time()) {
				kugel_i.set_collision(kugel_j, coll_time, 0);
			}
			if (coll_time < kugel_j.collision_time()) {
				kugel_j.set_collision(kugel_i, coll_time, 0);
			}
			if (coll_time < m_time) {
				next_collision_pair = CollisionPair<DIM>(kugel_i, kugel_j, coll_time, 0);
			}
		}
	}

	void first_collision() {
		for (int i = 0; i < vec_kugel.size(); i++) {
			calc_wall_collision_time(vec_kugel[i]);
			for (int j = i + 1; j < vec_kugel.size(); j++) {
				calc_collision_time(vec_kugel[i], vec_kugel[j]);
			}
		}
	}

	void next_collision() {
		Kugel<DIM> *kugel_i {next_collision_pair.kugel1()};
		for (auto& kugel_j : vec_kugel) {
			calc_collision_time(kugel_i, kugel_j);
		}
		kugel_i = next_collision_pair.kugel2();
		for (auto& kugel_j : vec_kugel) {
			calc_collision_time(kugel_i, kugel_j);
		}
	}

};
#endif
