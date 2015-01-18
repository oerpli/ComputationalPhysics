#include "cute.h"
#include "test_Kugel.h"

#include "Kugel.h"
#include "MatVec.h"

void constructorEmpty() {
	Kugel<3> k{};
	ASSERTM("", true);
}

void constructorMassLength_Mass() {
	massT km{3}; lengthT kr{5};
	Kugel<3> k{km,kr};
	ASSERTM("", k.mass() == km);
}

void constructorMassLength_R() {
	massT km{3}; lengthT kr{5};
	Kugel<3> k{km,kr};
	ASSERTM("", k.radius() == kr);
}

void copyConstructor() {
	massT km{3}; lengthT kr{5};
	Kugel<3> k1{km,kr};
	Kugel<3> k2{k1};
	ASSERTM("", k2.mass() == km && k2.radius() == kr);
}

void compareKugelIdentical() {
	Kugel<3> k{};
	ASSERTM("", k == k);
}

void compareKugelSame() {
	Kugel<3> k1{1,2}, k2{1,2};
	ASSERTM("", k1 == k2);
}

void setVelocity_Velocity() {
	Kugel<3> k{1, 1};
	MatVec<velocityT, 3> vel{3,4,5};

	k.velocity(vel);
	ASSERTM("", k.velocity() == vel);
}

void setVelocity_Energy() {
	Kugel<3> k{1, 1};
	MatVec<velocityT, 3> vel{3,4,5};
	energyT en{25};

	k.velocity(vel);
	ASSERTM("", k.ekin() == en);
}

void setPosition() {
	Kugel<3> k{1, 1};
	MatVec<lengthT, 3> pos{3,4,5};

	k.position(pos);
	ASSERTM("", k.position() == pos);
}

void kugel_fastForward() {
	Kugel<3> k{};
	MatVec<velocityT,3> vel{1,2,3};
	MatVec<lengthT,3> res_pos{3,6,9};

	k.velocity(vel);
	k.fast_forward(3);
	ASSERTM("", k.position() == res_pos);
}

cute::suite make_suite_Kugel(){
	cute::suite s;
	s.push_back(CUTE(constructorEmpty));
	s.push_back(CUTE(constructorMassLength_Mass));
	s.push_back(CUTE(constructorMassLength_R));
	s.push_back(CUTE(copyConstructor));
	s.push_back(CUTE(compareKugelSame));
	s.push_back(CUTE(setVelocity_Velocity));
	s.push_back(CUTE(setVelocity_Energy));
	s.push_back(CUTE(compareKugelIdentical));
	s.push_back(CUTE(setPosition));
	s.push_back(CUTE(kugel_fastForward));
	return s;
}


