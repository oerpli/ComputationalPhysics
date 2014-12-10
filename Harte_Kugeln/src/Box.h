#ifndef BOX_H
#define BOX_H

#include "Vec3D.h"
#include "Sphere.h"

#include <ostream>
#include <list>

class Box {
private:
	Vec3D<double> m_box_size;
	list<Sphere> m_spheres;
	
public:
	Box()= default;
	Box(const Box&)= delete;
	Box(Box&&)= delete;
	
	Box(long unsigned n, const Sphere& sph);
	Box(long unsigned n, double mass, double radius);
	
	void add(long unsigned n, const Sphere& sph);
	void add(long unsigned n, double mass, double radius);
	
	void collide(Sphere& sph1, Sphere& sph2);
	
	std::ostream& print(ostream& os) const ;
};

std::ostream& operator << (std::ostream& os, const Box& box);

#endif
