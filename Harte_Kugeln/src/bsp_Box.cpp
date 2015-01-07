#include <iostream>

#include "Box.h"

using namespace std;

int main() {
	const unsigned DIM {3};
	MatVec<lengthT,DIM> abmessung{2*m,2*m,2*m};
	Box<DIM> box{abmessung,10};

	cout << "Start\n" << box << '\n';
	box.initiate();
	cout << "after Init\n" << box << '\n';

}
