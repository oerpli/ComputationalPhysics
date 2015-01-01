#include <iostream>
#include <vector>
#include <algorithm>

#include <typeinfo>

#include "Kugel.h"
#include "MatVec.h"

using namespace std;

int main () {
	const unsigned dim{3};

	lengthT dia= 2 * 2.5 * m;
	MatVec<velocityT, dim> v_vel{3*mps, 5*mps, 2*mps};
	MatVec<lengthT, dim> v_pos{3*m, 1*m, 0*m};
	v_pos = v_pos * 0.5;

	Kugel<dim> kugel1{1 * kg, dia}, kugel2{1 * kg, dia};

	kugel1.position(v_pos);
	kugel2.position(-v_pos);

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
