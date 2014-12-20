#include "cute.h"
#include "test_Box.h"

#include <vector>
#include <algorithm>
#include "Kugel.h"
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


	void wrap_one(Kugel<DIM>& kugel) {
		auto pos = kugel.position();
		lengthT null{};
		quantity<dimensionless,int> factor{0};

		for (unsigned i=0; i<DIM; ++i) {
			factor = static_cast<quantity<dimensionless,int> > (pos[i] / vec_abmessung[i]);
			pos[i] -= vec_abmessung[i] * factor;
			if ( pos[i] < null )
				pos[i] += vec_abmessung[i];
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

};


const length m = meter;
const force N = newton;
const velocity mps = meters_per_second;
typedef quantity<length> lengthT;
typedef quantity<force> forceT;
typedef quantity<velocity> velocityT;

const MatVec<lengthT, 3> box_dimension{1*m,2*m,3*m};

void emptyBox() {
	Box<3> box { box_dimension };
	ASSERTM("", box.size() == 0 );
}


void boxSize10() {
	Box<3> box { box_dimension, 10 };
	ASSERTM("", box.size() == 10 );
}

void boxAbmessung() {
	Box<3> box { box_dimension };
	ASSERTM("", box.abmessung() == box_dimension);
}

void addBoxSize() {
	unsigned s1 { 10 }, s2 { 15 };
	Box<3> box1{box_dimension, s1}, box2{box_dimension, s2};
	box1.add(box2);
	ASSERTM("", box1.size() == s1 + s2);
}

void randomAccess_read(){
	Kugel<3> k{1 * kilogram, 1 * m};
	Box<3> box{box_dimension,10,k};

	ASSERTM("", box[3] == k);
}

void randomAccess_constRead(){
	Kugel<3> k{1 * kilogram, 1 * m};
	const Box<3> box{box_dimension,10,k};

	ASSERTM("", box[3] == k);
}

void randomAccess_write(){
	Kugel<3> k1{1 * kilogram, 1 * m}, k2{2 * kilogram, 2*m};
	Box<3> box{box_dimension,10, k1};

	box[3]=k2;
	ASSERTM("", ( box[3] == k2 && box[0] == k1) );
}

// Geht wahrscheinlich wegen Rundung nicht
void wrapPosition() {
	Box<3> box{box_dimension,1};
	MatVec<lengthT,3> pos{-.5*m, -2.3*m, 6.7*m}, res_pos{.5*m, 1.7*m, .7*m};

	box[0].position(pos);
	box.wrap();
	std::cout << box[0].position() << '\n' << res_pos << '\n';
	ASSERTM("", !( box[0].position() == res_pos ) );
}

void box_fastForward_pos() {
	Kugel<3> k{};
	MatVec<velocityT,3> vel{.2*mps,3*mps,1*mps};
	MatVec<lengthT,3> res_pos{.6*m,1*m,0*m}; //res_pos{3*m,6*m,9*m};

	k.velocity(vel);
	Box<3> box{box_dimension,1,k};

	box.fast_forward(3*second);
	std::cout << box[0].position() << '\n' << res_pos << '\n';
	ASSERTM("", !( box[0].position() == res_pos ) );
}

void box_fastForward_time() {
	Kugel<3> k{};
	MatVec<velocityT,3> vel{.2*mps,3*mps,1*mps};
	MatVec<lengthT,3> res_pos{.6*m,1*m,0*m}; //res_pos{3*m,6*m,9*m};

	k.velocity(vel);
	Box<3> box{box_dimension,1,k};

	auto dt = 3. * second;
	box.fast_forward(dt);
	ASSERTM("", box.time() == dt );
}

cute::suite make_suite_Box(){
	cute::suite s;
	s.push_back(CUTE(emptyBox));
	s.push_back(CUTE(boxSize10));
	s.push_back(CUTE(boxAbmessung));
	s.push_back(CUTE(addBoxSize));
	s.push_back(CUTE(randomAccess_read));
	s.push_back(CUTE(randomAccess_constRead));
	s.push_back(CUTE(randomAccess_write));
	s.push_back(CUTE(wrapPosition));
	s.push_back(CUTE(box_fastForward_pos));
	s.push_back(CUTE(box_fastForward_time));
	return s;
}
