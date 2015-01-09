#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "../src_sonstiges/MetaKugel.h"
#include "MatVec.h"
#include "Box.h"
using namespace std;

int main () {
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

	box.init_next_collision();
	std::cout << "\nafter collision" << std::endl;
	box[0].print();
	box[1].print();

	box.next_collision();
	std::cout << "\nafter next collision" << std::endl;
	box[0].print();
	box[1].print();

}
