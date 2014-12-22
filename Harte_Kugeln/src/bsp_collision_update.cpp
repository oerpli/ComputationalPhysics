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
#include "Box.h"
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

	const MatVec<lengthT, 3> box_dimension{10*m,10*m,10*m};

	Box<3> box { box_dimension , 2};

	lengthT dia= 1* m;
	MatVec<velocityT, dim> v_vel{1*mps, 0*mps, 0*mps};
	MatVec<lengthT, dim> v_pos{0*m, 0*m, 0*m};
	MatVec<lengthT, dim> v_pos2{4*m, 0*m, 0*m};

	v_pos = v_pos * 0.5;

	Kugel<dim> kugel1{1 * kg, dia}, kugel2{1 * kg, dia};

	kugel1.position(v_pos);
	kugel2.position(v_pos2);

	kugel1.velocity(v_vel);
	kugel2.velocity(-v_vel);

	box[0]=kugel1;
	box[1]=kugel2;

	box[0].print();
	box[1].print();

	box.first_collision();
	std::cout << "after collision" << std::endl;
	box[0].print();
	box[1].print();
}
