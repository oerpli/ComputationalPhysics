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


cute::suite make_suite_Kugel(){
	cute::suite s;
	s.push_back(CUTE(constructorEmpty));
	s.push_back(CUTE(constructorMassLength_Mass));
	s.push_back(CUTE(constructorMassLength_R));
	return s;
}
