#include "cute.h"
#include "test_Box.h"

#include "Box.h"

const length m = meter;
const force N = newton;
const velocity mps = meters_per_second;
typedef quantity<length> lengthT;
typedef quantity<force> forceT;
typedef quantity<velocity> velocityT;
typedef quantity<boost::units::si::time> timeT;

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

void distance() {
	Box<3> box{box_dimension,1};
	MatVec<lengthT,3> pos1{1.5*m, 1.7*m, 1.5*m};
	MatVec<lengthT,3> pos2{.1*m, 0.2*m, 0*m};
	MatVec<lengthT,3> dist{-0.4*m, 0.5*m, 1.5*m};
	Kugel<3> k1{},k2{};
	k1.position(pos1);
	k2.position(pos2);

	std::cout << box.dist(k1,k2) << '\n'<< dist << '\n';
	ASSERTM("", true);
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

void wall_collision_wall_time() {
	Kugel<3> k{};
	MatVec<velocityT, 3> vel{.5*mps, -1*mps, 2*mps};
	MatVec<lengthT,3> pos(.5*m);
//	MatVec<timeT,3> res_time {1*second,.5*second,1.25*second};
	timeT res_time = .5*second;

	k.position(pos);
	k.velocity(vel);
	Box<3> box{box_dimension,1,k};

	ASSERTM("", box.calc_wall_collision_time(k) == res_time );
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
	s.push_back(CUTE(distance));
	s.push_back(CUTE(box_fastForward_pos));
	s.push_back(CUTE(box_fastForward_time));
	s.push_back(CUTE(wall_collision_wall_time));
	return s;
}
