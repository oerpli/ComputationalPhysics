#include "Sphere.h"

#include "Vec3D.h"
#include <iostream>

Sphere::Sphere(double mass, double radius) : m_mass{mass}, m_radius{radius} {}

Sphere::Sphere(Sphere&& sph) { swap( *this, sph ); }

Sphere::Sphere(const Sphere& sph) :
	m_position{sph.m_position},
	m_velocity{sph.m_velocity},
	m_mass{sph.m_mass},
	m_radius{sph.m_radius} 
{ }

const Sphere& Sphere::operator = (Sphere sph) { 
	swap(*this, sph);
	return *this;
}
const Sphere& Sphere::operator = (Sphere&& sph) { 
	swap(*this, sph);
	return *this;
}


const Vec3D<double>& Sphere::position() const {return m_position;}

const Vec3D<double>& Sphere::position(const Vec3D<double>& pos) {
	return m_position = pos;
}

const Vec3D<double>& Sphere::velocity() const {return m_velocity;}

const Vec3D<double>& Sphere::velocity(const Vec3D<double>& pos) {
	return m_velocity = pos;
}

ostream& Sphere::print(ostream & os) const {
	os << " mas: " << m_mass;
	os << " rad: " << m_radius;
	os << " pos: " << m_position;
	os << " vel: " << m_velocity;
	return os;
}



std::ostream& operator << (std::ostream& os,const Sphere & s) {
	return s.print(os);
}
