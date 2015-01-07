#include <iostream>

#include "Box.h"

using namespace std;

int main() {
	const unsigned DIM {3};
	MatVec<lengthT,DIM> abmessung{2*m,2*m,2*m};
	Kugel<DIM> kugel1{1*kg, .1*m};

	Box<DIM> box{abmessung, 10, kugel1};

	if(! box.initiate()) return 1;
	cout << "after Init\n" << box << '\n';
}
