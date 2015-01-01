#include "cute.h"
#include "test_Kugel.h"

#include "Kugel.h"
#include "MatVec.h"

void constructorEmpty() {
	Kugel<3> k{};
	ASSERTM("", true);
}

void constructorMassLength_Mass() {
	massT km{3*kg}; lengthT kr{5*m};
	Kugel<3> k{km,kr};
	ASSERTM("", k.mass() == km);
}

void constructorMassLength_R() {
	massT km{3*kg}; lengthT kr{5*m};
	Kugel<3> k{km,kr};
	ASSERTM("", k.radius() == kr);
}

void compareKugelIdentical() {
	Kugel<3> k{};
	ASSERTM("", k == k);
}

void compareKugelSame() {
	Kugel<3> k1{1*kg,2*m}, k2{1*kg,2*m};
	ASSERTM("", k1 == k2);
}

void setVelocity_Velocity() {
	Kugel<3> k{1*kg, 1*m};
	MatVec<velocityT, 3> vel{3*mps,4*mps,5*mps};

	k.velocity(vel);
	ASSERTM("", k.velocity() == vel);
}

void setVelocity_Energy() {
	Kugel<3> k{1*kg, 1*m};
	MatVec<velocityT, 3> vel{3*mps,4*mps,5*mps};
	energyT en{25 * mps*mps*kg};

	k.velocity(vel);
	ASSERTM("", k.ekin() == en);
}

void setPosition() {
	Kugel<3> k{1*kg, 1*m};
	MatVec<lengthT, 3> pos{3*m,4*m,5*m};

	k.position(pos);
	ASSERTM("", k.position() == pos);
}

void kugel_fastForward() {
	Kugel<3> k{};
	MatVec<velocityT,3> vel{1*mps,2*mps,3*mps};
	MatVec<lengthT,3> res_pos{3*m,6*m,9*m};

	k.velocity(vel);
	k.fast_forward(3*s);
	ASSERTM("", k.position() == res_pos);
}

cute::suite make_suite_Kugel(){
	cute::suite s;
	s.push_back(CUTE(constructorEmpty));
	s.push_back(CUTE(constructorMassLength_Mass));
	s.push_back(CUTE(constructorMassLength_R));
	s.push_back(CUTE(compareKugelSame));
	s.push_back(CUTE(setVelocity_Velocity));
	s.push_back(CUTE(setVelocity_Energy));
	s.push_back(CUTE(compareKugelIdentical));
	s.push_back(CUTE(setPosition));
	s.push_back(CUTE(kugel_fastForward));
	return s;
}


