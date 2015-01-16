#ifndef UNITS_TYPEDEF_H
#define UNITS_TYPEDEF_H

#include "Config.h"

#ifdef USE_BOOST_UNITS
	#include "my_units.hpp"

	typedef Quantity<1,0,0> massT;
	typedef Quantity<0,1,0> lengthT;
	typedef Quantity<0,2,0> areaT;
	typedef Quantity<0,3,0> volumeT;
	typedef Quantity<0,0,1> timeT;
	typedef Quantity<0,1,-1> velocityT;
	typedef Quantity<0,1,-2> accelerationT;
	typedef Quantity<1,2,-2> energyT;
	typedef Quantity<0,0,0> dimlessT;
	typedef Quantity<1,1,-2> forceT;

	constexpr massT kg(1.0);
	constexpr lengthT m(1.0);
	constexpr energyT J(1.0);
	constexpr velocityT mps(1.0);
	constexpr timeT s(1.0);
	constexpr forceT N(1.0);

	#define Pow(base,exp) ( unit_pow<(exp)>((base)) )

#else
	typedef double lengthT;
	typedef double timeT;
	typedef double velocityT;
	typedef double massT;
	typedef double forceT;
	typedef double energyT;
	typedef double dimlessT;

	const double kg { 1.0 };
	const double m { 1.0 };
	const double N { 1.0 };
	const double mps { 1.0 };
	const double s { 1.0 };

	#include <cmath>
	#define Pow(base,exp) ( pow( (base), (exp) ) )

#endif //USE_BOOST_UNITS

#endif // UNITS_TYPEDEF_H
