#include <iostream>
#include <vector>
#include <algorithm>
//Bin noch nicht so vertraut mit Units, hab einfach mal einige reingeladen...
#include <boost/units/cmath.hpp>
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>

#include <typeinfo>

#include "MatVec.h"
#include "Kugel.h"

using namespace std;
using namespace boost::units;
using namespace boost::units::si;

int main () {
	const length m = meter;
	const velocity mps = meters_per_second;
	const mass kg = kilogram;

	typedef quantity<length> lengthT;
	typedef quantity<velocity> velocityT;

	const unsigned dim{3};

	lengthT dia= 2 * 2.5 * m;
	MatVec<velocityT, dim> v_vel{3*mps, 5*mps, 2*mps};
	MatVec<lengthT, dim> v_pos{3*m, 1*m, 0*m};
	v_pos = v_pos * 0.5;

	Kugel<dim> kugel1{1 * kg, dia}, kugel2{1 * kg, dia};

	kugel1.vec_pos = v_pos;
	kugel2.vec_pos = -v_pos;

	kugel1.velocity(v_vel);
	kugel2.velocity(-v_vel);

	cout << "Kugel1:\n" << kugel1 << '\n';
	cout << "Kugel2:\n" << kugel2 << '\n';
	cout << "Energy: " << kugel1.ekin() + kugel2.ekin() << '\n';

	cout << "\nKollision:\n\n";
	collide(kugel1, kugel2);

	cout << "Kugel1:\n" << kugel1 << '\n';
	cout << "Kugel2:\n" << kugel2 << '\n';
	cout << "Energy: " << kugel1.ekin() + kugel2.ekin() << '\n';

}
