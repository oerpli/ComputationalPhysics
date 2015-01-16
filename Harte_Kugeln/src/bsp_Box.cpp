#include <iostream>

#include "Box.h"

using namespace std;

int main() {
	const unsigned DIM {3};
	MatVec<lengthT,DIM> abmessung{2,2,2};
	Kugel<DIM> kugel1{1, .1};

	Box<DIM> box{abmessung, 10, kugel1};

	if(! box.initiate()) return 1;
	cout << "after Init\n" << box << '\n';

	MatVec<velocityT,DIM> vel_com {};
	energyT ekin {};
	box.unitary([&](const Kugel<DIM>& k){vel_com += k.velocity(); ekin += k.ekin();});

	cout << "com Vel: " << vel_com << "\nekin: " << ekin << '\n';
}
