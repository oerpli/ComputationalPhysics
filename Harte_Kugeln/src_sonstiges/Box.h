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

	timeT m_time;
	std::vector<Kugel<DIM>> vec_kugel;
	MatVec<lengthT, DIM> vec_abmessung;
	CollisionPair<DIM> next_collision_pair;

	void wrap_one(Kugel<DIM>& kugel) {
		auto pos = kugel.position();
		lengthT null{};
		quantity<dimensionless,int> factor{0};

		for (unsigned i=0; i<DIM; ++i) {
			factor = static_cast<quantity<dimensionless,int> > (pos[i] / (vec_abmessung[i]*0.5));
			pos[i] -= vec_abmessung[i] * factor;
		}
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
		: m_time{},vec_kugel(size, kugel), vec_abmessung{dim} { wrap(); }
	Box(const MatVec<lengthT, DIM>& dim, unsigned size)
		: m_time{}, vec_kugel(size), vec_abmessung{dim} {}
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

	void calc_wall_collision_time(Kugel<DIM>& kugel) {
		MatVec<lengthT, DIM> riw { };
		MatVec<lengthT, DIM> viw { };
		timeT coll_time { };
		for (int j = -1; j < 2; j = j + 2) {
			MatVec<lengthT,DIM> wall {j*vec_abmessung/2};
			for (int k = 0; k < DIM; k++) {
				auto riw = wall[k]-kugel.position()[k];
				auto viw = -kugel.velocity()[k];
				if (riw*viw < 0) {
					coll_time = (- riw * viw - sqrt(pow(riw*viw,2) - (viw*viw)*(riw*riw - pow(kugel.radius()*0.5, 2))))/(viw*viw);
					if (coll_time < kugel.collision_time()) {
						kugel.set_collision(kugel, coll_time, 1);
					}
					if (coll_time < m_time) {
						next_collision_pair = CollisionPair<DIM>(kugel, kugel, coll_time, 1);
					}
				}
			}
		}
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
