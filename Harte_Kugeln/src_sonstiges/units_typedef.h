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


	constexpr massT operator"" _kg(double long x)  { return massT(x); }
	constexpr massT operator"" _kg(unsigned long long x)  { return massT(static_cast<double>(x)); }
	constexpr lengthT operator"" _m(double long x)  { return lengthT(x); }
	constexpr lengthT operator"" _m(unsigned long long x)  { return lengthT(static_cast<double>(x)); }
	constexpr velocityT operator"" _mps(double long x)  { return velocityT(x); }
	constexpr velocityT operator"" _mps(unsigned long long x)  { return velocityT(static_cast<double>(x)); }
	constexpr energyT operator"" _J(double long x)  { return energyT(x); }
	constexpr energyT operator"" _J(unsigned long long x)  { return energyT(static_cast<double>(x)); }
	constexpr forceT operator"" _N(double long x)  { return forceT(x); }
	constexpr forceT operator"" _N(unsigned long long x)  { return forceT(static_cast<double>(x)); }
	constexpr timeT operator"" _s(double long x)  { return timeT(x); }
	constexpr timeT operator"" _s(unsigned long long x)  { return timeT(static_cast<double>(x)); }


#endif // UNITS_TYPEDEF_H
