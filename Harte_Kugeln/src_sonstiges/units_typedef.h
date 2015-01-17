#ifndef UNITS_TYPEDEF_H
#define UNITS_TYPEDEF_H

#include "Config.h"

#ifdef USE_BOOST_UNITS
	#include "my_units.hpp"

	template<int num, unsigned den>
	using R = Rational<num, den>;

	typedef Quantity<R<1,1>,R<0,1>,R<0,1>> massT;
	typedef Quantity<R<0,1>,R<1,1>,R<0,1>> lengthT;
	typedef Quantity<R<0,1>,R<2,1>,R<0,1>> areaT;
	typedef Quantity<R<0,1>,R<3,1>,R<0,1>> volumeT;
	typedef Quantity<R<0,1>,R<0,1>,R<1,1>> timeT;
	typedef Quantity<R<0,1>,R<1,1>,R<-1,1>> velocityT;
	typedef Quantity<R<0,1>,R<1,1>,R<-2,1>> accelerationT;
	typedef Quantity<R<1,1>,R<2,1>,R<-2,1>> energyT;
	typedef Quantity<R<0,1>,R<0,1>,R<0,1>> dimlessT;
	typedef Quantity<R<1,1>,R<1,1>,R<-2,1>> forceT;

	constexpr massT kg(1.0);
	constexpr lengthT m(1.0);
	constexpr energyT J(1.0);
	constexpr velocityT mps(1.0);
	constexpr timeT s(1.0);
	constexpr forceT N(1.0);

	#define Pow(base,exp) ( unit_pow<(exp)>((base)) )

	template<class M, class L, class T>
	constexpr Quantity<M,L,T> round(const Quantity<M,L,T>& q) {
		return Quantity<M,L,T>{round( double(q) )};
	}

	template<class M, class L, class T>
	constexpr Quantity<M,L,T> floor(const Quantity<M,L,T>& q) {
		return Quantity<M,L,T>{floor( double(q) )};
	}

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
