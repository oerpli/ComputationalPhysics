#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3D.h"

#include <iostream>

class Sphere{
private:
	Vec3D<double> m_position, m_velocity;
	double m_mass, m_radius;
	Sphere();
public:	
	Sphere(Sphere && sph);
	Sphere(const Sphere & sph);
	Sphere(double mass, double radius);
	Sphere(const double* position, const double* velocity);
	
	friend void swap(Sphere& sphA, Sphere& sphB) {
			swap(sphA.m_position, sphB.m_position);
			swap(sphA.m_velocity, sphB.m_velocity);
			std::swap(sphA.m_mass, sphB.m_mass);
			std::swap(sphA.m_radius, sphB.m_radius);
	}
	const Sphere& operator = (Sphere sph);
	const Sphere& operator = (Sphere&& sph);
	
	const Vec3D<double>& position() const;
	const Vec3D<double>& position(const Vec3D<double> & position);
	
	const Vec3D<double>& velocity() const;
	const Vec3D<double>& velocity(const Vec3D<double> & velocity);
	
	std::ostream& print(std::ostream & os = std::cout) const;
};


std::ostream& operator << (std::ostream& os,const Sphere & v);

#endif
