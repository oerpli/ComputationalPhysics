#include "cute.h"
#include "test_CollisionPair.h"

#include "CollisionPair.h"
#include "Kugel.h"
#include <boost/units/systems/si.hpp>

using namespace std;

void typeCastBool() {
	Kugel<3> k{};
	CollisionPair<3> cp{k,k};

	ASSERTM("", ! cp);
}

void setBool() {
	Kugel<3> k{};
	CollisionPair<3> cp{k,k};
	cp.set_collision(1*second,true);
	ASSERTM("", cp);
}

void compareTimeSimpleLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0 * second, true}, cp2{k,k, 2.0 * second, true};
	ASSERTM("", cp1 < cp2);
}

void compareTimeSimpleGreater() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0 * second, true}, cp2{k,k, 2.0 * second, true};
	ASSERTM("", cp2 > cp1);
}

void compareTimeCollisionTrueFalseLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0 * second, true}, cp2{k,k, 2.0 * second, false};
	ASSERTM("", cp1 < cp2 );
}

/*
void compareTimeCollisionFalseTrueLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0 * second, false}, cp2{k,k, 2.0 * second, true};
	ASSERTM("", ! ( cp1 < cp2 ) );
}
*/

void equalSame() {
	Kugel<3> k{};
	CollisionPair<3> cp{k,k, 1.0 * second, false};
	ASSERTM("", cp.equal(cp));
}

void equalDiffButIdentKugel() {
	Kugel<3> k1{}, k2{};
	CollisionPair<3> cp1{k1,k1}, cp2{k2,k2};
	ASSERTM("", ! cp1.equal(cp2));
}

void equalIdent() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0 * second, true}, cp2{k,k, 1.0 * second, true};
	ASSERTM("", cp1.equal(cp2));
}

void equalFalseCollisionSameTime() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k, 1.0 * second, false}, cp2{k,k, 1.0 * second, true};
	ASSERTM("", ! cp1.equal(cp2));
}

void assignment() {
	Kugel<3> k1{},k2{};
	CollisionPair<3> cp1{k1,k1}, cp2{k2,k2, 2*second, true};
	cp1 = cp2;
	ASSERTM("", cp1 == cp2);
}

void assignLower() {
	Kugel<3> k{};
	CollisionPair<3> cp1{k,k,2.0 * second,false}, cp2{k,k,1.0 * second,true};
	cp1 <= cp2;
	ASSERTM("", cp1 == cp2);
}


cute::suite make_suite_CollisionPair(){
	cute::suite s;

	s.push_back(CUTE(typeCastBool));
	s.push_back(CUTE(setBool));
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
	return s;
}
