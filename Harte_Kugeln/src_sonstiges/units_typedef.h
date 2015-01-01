#ifndef UNITS_TYPEDEF_H
#define UNITS_TYPEDEF_H

#include "Config.h"

#ifdef USE_BOOST_UNITS
	#include <boost/units/cmath.hpp>
	#include <boost/units/pow.hpp>
	#include <boost/units/systems/si.hpp>
	#include <boost/units/systems/si/io.hpp>
	#include <boost/units/systems/si/base.hpp>
	#include <boost/units/derived_dimension.hpp>

	#include <boost/units/physical_dimensions/length.hpp>
	#include <boost/units/physical_dimensions/mass.hpp>
	#include <boost/units/physical_dimensions/time.hpp>


	typedef boost::units::quantity< boost::units::si::length , double > lengthT;
	typedef boost::units::quantity< boost::units::si::time , double > timeT;
	typedef boost::units::quantity< boost::units::si::velocity , double > velocityT;
	typedef boost::units::quantity< boost::units::si::mass , double > massT;
	typedef boost::units::quantity< boost::units::si::force , double > forceT;
	typedef boost::units::quantity< boost::units::si::energy , double > energyT;
	typedef boost::units::quantity< boost::units::si::dimensionless , int > idimlessT;

	const boost::units::si::mass kg = boost::units::si::kilogram;
	const boost::units::si::length m = boost::units::si::meter;
	const boost::units::si::force N = boost::units::si::newton;
	const boost::units::si::velocity mps = boost::units::si::meters_per_second;
	const boost::units::si::time s = boost::units::si::second;

#else
	typedef double lengthT;
	typedef double timeT;
	typedef double velocityT;
	typedef double massT;
	typedef double forceT;
	typedef double energyT;
	typedef double idimlessT;

	const double kg { 1.0 };
	const double m { 1.0 };
	const double N { 1.0 };
	const double mps { 1.0 };
	const double s { 1.0 };

#endif //USE_BOOST_UNITS

#endif // UNITS_TYPEDEF_H
