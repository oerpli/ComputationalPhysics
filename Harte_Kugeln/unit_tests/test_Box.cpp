#include "cute.h"
#include "test_Box.h"

#include "Box.h"

const MatVec<lengthT, 3> box_dimension{10,20,30};
const unsigned DIM3{3};

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
	Kugel<3> k{1, 1};
	Box<3> box{box_dimension,10,k};

	ASSERTM("", box[3] == k);
}

void randomAccess_constRead(){
	Kugel<3> k{1, 1};
	const Box<3> box{box_dimension,10,k};

	ASSERTM("", box[3] == k);
}

void randomAccess_write(){
	Kugel<3> k1{1, 1}, k2{2, 2};
	Box<3> box{box_dimension,10, k1};

	box[3]=k2;
	ASSERTM("", ( box[3] == k2 && box[0] == k1) );
}

// Geht wahrscheinlich wegen Rundung nicht
void wrapPosition() {
	Box<3> box{box_dimension,1};
	MatVec<lengthT,3> pos{-5, -23, 67}, res_pos{5, 17, 7};

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
	MatVec<velocityT,3> vel{2,30,10};
	MatVec<lengthT,3> res_pos{6,10,0}; //res_pos{3*m,6*m,9*m};

	k.velocity(vel);
	Box<3> box{box_dimension,1,k};

	box.fast_forward(3);
	std::cout << box[0].position() << '\n' << res_pos << '\n';
	ASSERTM("", box[0].position() == res_pos);
}

void box_fastForward_time() {
	Kugel<3> k{};
	MatVec<velocityT,3> vel{2,30,10};
	MatVec<lengthT,3> res_pos{6,10,0}; //res_pos{3*m,6*m,9*m};

	k.velocity(vel);
	Box<3> box{box_dimension,1,k};

	auto dt = 3. * s;
	box.fast_forward(dt);
	ASSERTM("", box.time() == dt );
}

void box_initiate_given_no_rand() {
	MatVec<lengthT,3> pos1 {5}, pos2 {1};
	Box<3> box{box_dimension, 2, Kugel<3>{1, .1}};

	box[0].position(pos1);
	box[1].position(pos2);
	box.initiate();

	ASSERTM("", box[0].position() == pos1 && box[1].position() == pos2);
}

void box_initiate_given_rand() {
	MatVec<lengthT,3> pos {5};
	Box<3> box{box_dimension, 2, Kugel<3>{1, .1}};

	box[0].position(pos);
	box[1].position(pos);
	box.initiate();

	ASSERTM("", box[0].position() != pos || box[1].position() != pos);
}

void box_collision_time_simple() {
	MatVec<lengthT,3> pos{5, 0, 0};
	MatVec<velocityT,3> vel {1, 0, 0};
	Box<3> box{box_dimension, 2, Kugel<3>{4, 1}};

	box[0].position(pos);
	box[0].velocity(vel);
	box.initiate();

	auto coll_time = box.collide();
	ASSERTM("", coll_time == timeT{3});
}

void problem_3_kugeln_Abraham_1() {
	MatVec<lengthT,DIM3> pos_urspr{10, 10, 0};
	MatVec<lengthT,DIM3> pos1{0, -1, 0};
	MatVec<lengthT,DIM3> pos2{0, 2, 0};
	MatVec<lengthT,DIM3> pos3{-4, 2, 0};

	pos1 += pos_urspr; pos2 += pos_urspr; pos3 += pos_urspr;

	MatVec<velocityT,DIM3> vel12{0, 1, 0};
	MatVec<velocityT,DIM3> vel3{1, 0, 0};

	Box<DIM3> box{MatVec<lengthT,DIM3>{20, 20, 20}, 3, Kugel<DIM3>{2_kg, .5_m}};
	box[0].position(pos1); box[0].velocity(vel12);
	box[1].position(pos2); box[1].velocity(-vel12);
	box[2].position(pos3); box[2].velocity(vel3);

	box.initiate();
	box.collide(); box.collide();

	ASSERTM("", box[0].position() == ( MatVec<lengthT,DIM3>{10, 1, 0} ));
}

void problem_3_kugeln_Abraham_2() {
	MatVec<lengthT,DIM3> pos_urspr{10, 10, 0};
	MatVec<lengthT,DIM3> pos1{0, -1, 0};
	MatVec<lengthT,DIM3> pos2{0, 2, 0};
	MatVec<lengthT,DIM3> pos3{-4, 2, 0};
	MatVec<lengthT,DIM3> pos4{5, 2, 0};

	pos1 += pos_urspr; pos2 += pos_urspr;
	pos3 += pos_urspr; pos4 += pos_urspr;

	MatVec<velocityT,DIM3> vel12{0, 1, 0};
	MatVec<velocityT,DIM3> vel3{1, 0, 0};

	Box<DIM3> box{MatVec<lengthT,DIM3>{20, 20, 20}, 4, Kugel<DIM3>{2_kg, .5_m}};
	box[0].position(pos1); box[0].velocity(vel12);
	box[1].position(pos2); box[1].velocity(-vel12);
	box[2].position(pos3); box[2].velocity(vel3);
	box[3].position(pos4); box[3].velocity(-vel3);

	box.initiate();
	box.collide(); box.collide();

	ASSERTM("", box[2].position() == ( MatVec<lengthT,DIM3>{10, 12, 0} ));
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
	s.push_back(CUTE(problem_3_kugeln_Abraham_1));
	s.push_back(CUTE(problem_3_kugeln_Abraham_2));
	return s;
}
