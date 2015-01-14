#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "MatVec.h"
#include "Box.h"
using namespace std;

int main () {
	const unsigned dim{3};
	MatVec<lengthT,dim> pos{8 *m, 0 *m, 0 *m};
	MatVec<velocityT,dim> vel {1 *mps, 0 *mps, 0 *mps};
	Box<3> box{MatVec<lengthT,dim>{10*m}, 2, Kugel<dim>{4 *kg, 1 *m}};
	timeT coll_time{};

	box[0].position(pos);
	box[1].velocity(vel);
	box.initiate();

	cout << box;
	coll_time = box.collide();
	cout << coll_time << '\n';
	cout << box;
	coll_time = box.collide();
	cout << coll_time << '\n';
	cout << box;
	coll_time = box.collide();
	cout << coll_time << '\n';
	cout << box;

}
