#include "cute.h"
#include "test_Kugel.h"

#include "Kugel.h"

#include "MatVec.h"


const mass kg = kilogram;
const length m = meter;
const force N = newton;
const velocity mps = meters_per_second;

typedef quantity<mass> massT;
typedef quantity<length> lengthT;
typedef quantity<force> forceT;
typedef quantity<velocity> velocityT;

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
	boost::units::quantity<boost::units::si::energy> en{25 * mps*mps*kg};

	k.velocity(vel);
	ASSERTM("", k.ekin() == en);
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
	return s;
}
