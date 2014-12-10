#include "Box.h"

#include "Vec3D.h"
#include "Sphere.h"

#include <ostream>

using namespace std;


Box::Box(long unsigned n, const Sphere& sph) { add( n, sph ); }
Box::Box(long unsigned n, double mass, double radius) { add( n, mass, radius ); }

void Box::add(long unsigned n, const Sphere& sph) {
	m_spheres.insert(m_spheres.end(), n, sph);
}

void Box::add(long unsigned n, double mass, double radius) { add( n, Sphere{mass,radius} ); }

void Box::collide(Sphere& sph1, Sphere& sph2) {
	Vec3D<double> d{sph2.position()};
	d -= sph1.position();
	d /= d.norm();	
	Vec3D<double> v1{sph1.velocity()}, v2{sph2.velocity()};
	Vec3D<double> v1R{d}, v2R{d};
	Vec3D<double> v_rel;

	v1R *= d * v1;
	v2R *= d * v2;
	
	v_rel = v2R - v1R;
	v_rel *= 2 / ( sph1.mass() + sph2.mass() );
	
	sph1.velocity( v1 + v_rel * sph2.mass() );
	sph2.velocity( v2 - v_rel * sph1.mass() );
	 
}

ostream& Box::print(ostream& os) const {
	for (auto& sph : m_spheres) os << sph << endl;
	return os;
}


ostream& operator << (ostream& os, const Box& box) { return box.print(os); }
