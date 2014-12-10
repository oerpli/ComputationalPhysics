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
	Box()= delete;
	Box(const Box&)= delete;
	Box(Box&&)= delete;
	
	Box(long unsigned element_number, const Sphere& sph);
	Box(long unsigned element_number, double mass, double radius);
	
	std::ostream& print(ostream& os) const ;
};

std::ostream& operator << (std::ostream& os, const Box& box);

#endif
