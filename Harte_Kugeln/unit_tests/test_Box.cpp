#include "cute.h"
#include "test_Box.h"

#include "Box.h"

const MatVec<lengthT, 3> box_dimension{10*m,20*m,30*m};

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
	Kugel<3> k{1 * kg, 1 * m};
	Box<3> box{box_dimension,10,k};

	ASSERTM("", box[3] == k);
}

void randomAccess_constRead(){
	Kugel<3> k{1 * kg, 1 * m};
	const Box<3> box{box_dimension,10,k};

	ASSERTM("", box[3] == k);
}

void randomAccess_write(){
	Kugel<3> k1{1 * kg, 1 * m}, k2{2 * kg, 2*m};
	Box<3> box{box_dimension,10, k1};

	box[3]=k2;
	ASSERTM("", ( box[3] == k2 && box[0] == k1) );
}

// Geht wahrscheinlich wegen Rundung nicht
void wrapPosition() {
	Box<3> box{box_dimension,1};
	MatVec<lengthT,3> pos{-5*m, -23*m, 67*m}, res_pos{5*m, 17*m, 7*m};

	box[0].position(pos);
	box.wrap();
	std::cout << box[0].position() << '\n' << res_pos << '\n';
	ASSERTM("", box[0].position() == res_pos );
}
/*
void kugel_distance() {
	Box<3> box{box_dimension,1};
	MatVec<lengthT,3> pos1{15*m, 17*m, 15*m};
	MatVec<lengthT,3> pos2{1*m, 2*m, 0*m};
	MatVec<lengthT,3> dist{-4*m, 5*m, 15*m};
	Kugel<3> k1{},k2{};
	k1.position(pos1);
	k2.position(pos2);

	std::cout << box.dist(k1,k2) << '\n'<< dist << '\n';
	ASSERTM("", box.dist(k1,k2) == dist && box.dist(k2,k1) == -dist);
}
*/

void box_fastForward_pos() {
	Kugel<3> k{};
	MatVec<velocityT,3> vel{2*mps,30*mps,10*mps};
	MatVec<lengthT,3> res_pos{6*m,10*m,0*m}; //res_pos{3*m,6*m,9*m};

	k.velocity(vel);
	Box<3> box{box_dimension,1,k};

	box.fast_forward(3*s);
	std::cout << box[0].position() << '\n' << res_pos << '\n';
	ASSERTM("", box[0].position() == res_pos);
}

void box_fastForward_time() {
	Kugel<3> k{};
	MatVec<velocityT,3> vel{2*mps,30*mps,10*mps};
	MatVec<lengthT,3> res_pos{6*m,10*m,0*m}; //res_pos{3*m,6*m,9*m};

	k.velocity(vel);
	Box<3> box{box_dimension,1,k};

	auto dt = 3. * s;
	box.fast_forward(dt);
	ASSERTM("", box.time() == dt );
}

void box_initiate_given_no_rand() {
	MatVec<lengthT,3> pos1 { 5 *m }, pos2 {1 *m};
	Box<3> box{box_dimension, 2, Kugel<3>{1 *kg, .1 *m}};

	box[0].position(pos1);
	box[1].position(pos2);
	box.initiate();

	ASSERTM("", box[0].position() == pos1 && box[1].position() == pos2);
}

void box_initiate_given_rand() {
	MatVec<lengthT,3> pos { 5 *m };
	Box<3> box{box_dimension, 2, Kugel<3>{1 *kg, .1 *m}};

	box[0].position(pos);
	box[1].position(pos);
	box.initiate();

	ASSERTM("", box[0].position() != pos || box[1].position() != pos);
}

void box_collision_time_simple() {
	MatVec<lengthT,3> pos{5 *m, 0 *m, 0 *m};
	MatVec<velocityT,3> vel {1 *mps, 0 *mps, 0 *mps};
	Box<3> box{box_dimension, 2, Kugel<3>{4 *kg, 1 *m}};

	box[0].position(pos);
	box[0].velocity(vel);
	box.initiate();

	auto coll_time = box.collide();
	ASSERTM("", coll_time == 3 *s);
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
//	s.push_back(CUTE(kugel_distance));
	s.push_back(CUTE(box_fastForward_pos));
	s.push_back(CUTE(box_fastForward_time));
	s.push_back(CUTE(box_initiate_given_no_rand));
	s.push_back(CUTE(box_initiate_given_rand));
	s.push_back(CUTE(box_collision_time_simple));
	return s;
}
