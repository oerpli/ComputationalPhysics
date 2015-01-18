#include "cute.h"
#include "test_CollisionPair.h"

#include "CollisionPair.h"
#include "Kugel.h"

using namespace std;

void typeCastBool() {
	CollisionPair<3> cp{};

	ASSERTM("", ! cp);
}

void compareTimeSimpleLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0, true}, cp2{k,k, 2.0, true};
	ASSERTM("", cp1 < cp2);
}

void compareTimeSimpleGreater() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0, true}, cp2{k,k, 2.0, true};
	ASSERTM("", cp2 > cp1);
}

void compareTimeCollisionTrueFalseLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0, true}, cp2{k,k, 2.0, false};
	ASSERTM("", cp1 < cp2 );
}

/*
void compareTimeCollisionFalseTrueLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0 * s, false}, cp2{k,k, 2.0 * s, true};
	ASSERTM("", ! ( cp1 < cp2 ) );
}
*/

void equalSame() {
	Kugel<3> k{};
	CollisionPair<3> cp{k,k, 1.0, false};
	ASSERTM("", cp == cp);
}

void equalDiffButIdentKugel() {
	Kugel<3> k1{}, k2{};
	CollisionPair<3> cp1{k1}, cp2{k2};
	ASSERTM("", ! (cp1 == cp2));
}

void equalIdent() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0, true}, cp2{k,k, 1.0, true};
	ASSERTM("", cp1 == cp2);
}

void equalFalseCollisionSameTime() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0, false}, cp2{k,k, 1.0, true};
	ASSERTM("", ! (cp1 == cp2));
}

void assignment() {
	Kugel<3> k{};
	CollisionPair<3> cp1{}, cp2{k,k, 2, true};
	cp1 = cp2;
	ASSERTM("", cp1 == cp2);
}

void assignLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k,2.0,false}, cp2{k,k,1.0,true};
	cp1 <= cp2;
	ASSERTM("", cp1 == cp2);
}

void get_kugel1() {
	Kugel<3> k1{}, k2{};
	MatVec<velocityT,3> vel{1,2,3};
	CollisionPair<3> cp{k1,k2,1,false};

	k1.velocity(vel);
	ASSERTM("", &cp.kugel1() == &k1);
}

void get_kugel2() {
	Kugel<3> k1{}, k2{};
	CollisionPair<3> cp{k1,k2,1,false};

	ASSERTM("", &cp.kugel2() == &k2);
}

cute::suite make_suite_CollisionPair(){
	cute::suite s;

	s.push_back(CUTE(typeCastBool));
	s.push_back(CUTE(compareTimeSimpleLower));
	s.push_back(CUTE(compareTimeSimpleGreater));
	s.push_back(CUTE(compareTimeCollisionTrueFalseLower));
//	s.push_back(CUTE(compareTimeCollisionFalseTrueLower));
	s.push_back(CUTE(equalDiffButIdentKugel));
	s.push_back(CUTE(equalSame));
	s.push_back(CUTE(equalIdent));
	s.push_back(CUTE(equalFalseCollisionSameTime));
	s.push_back(CUTE(assignment));
	s.push_back(CUTE(assignLower));
	s.push_back(CUTE(get_kugel1));
	s.push_back(CUTE(get_kugel2));
	return s;
}

