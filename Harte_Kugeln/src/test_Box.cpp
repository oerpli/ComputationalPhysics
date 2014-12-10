#include <iostream>
#include <cmath>

#include "Vec3D.h"
#include "Box.h"

using namespace std;

inline double energy(const Sphere& sph) {
	return sph.mass()/2*(( sph.position())^2 ).sum();
}

int main() {
	double r=2.5;
	Vec3D <double> v_pos{3,1,0}, v_vel{3,5,2};
	v_pos *= .5;
	Sphere sph1{1,r}, sph2{1,r};
	Box box;
	
	sph1.position(v_pos);
	sph2.position(-v_pos);
	
	sph1.velocity(v_vel);
	sph2.velocity(-v_vel);
	
	cout << sph1 << endl << sph2 << endl;
	cout << "Energy: " << energy(sph1) + energy(sph2) << endl;
	
	cout << "Kollision" << endl;
	box.collide(sph1, sph2);
	
	cout << sph1 << endl << sph2 << endl;
	cout << "Energy: " << energy(sph1) + energy(sph2) << endl;
	
return 0;
}
