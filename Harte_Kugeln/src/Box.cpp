#include "Box.h"

#include "Vec3D.h"
#include "Sphere.h"

#include <ostream>

using namespace std;


Box::Box(long unsigned n, const Sphere& sph) : m_spheres{ n, sph } {}
Box::Box(long unsigned n, double mass, double radius) : m_spheres{ n, Sphere{mass,radius} } {}

ostream& Box::print(ostream& os) const {
	for (auto& sph : m_spheres) os << sph << endl;
	return os;
}


ostream& operator << (ostream& os, const Box& box) { return box.print(os); }
