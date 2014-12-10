#ifndef VEC3D_H
#define VEC3D_H

#include <ostream>

template <class Type> class Vec3D {
private:
	Type m_vec[3];
	
	const Vec3D<Type>& add(const Vec3D<Type>& v);
	const Vec3D<Type>& make_negative();
	
public:
	Vec3D(Type a = 0, Type b = 0, Type c = 0);
	Vec3D(const Type * array);
	Vec3D(const Vec3D<Type> & v);
	Vec3D(Vec3D<Type>&& v);
	
	friend void swap(Vec3D<Type>& va, Vec3D<Type>& vb) {
		std::swap(va.m_vec, vb.m_vec);
	}
	
	Type& operator [] (int i);
	const Type& operator [] (int i) const;
	
	const Vec3D<Type>& operator = (Vec3D<Type> v);
	
	Vec3D<Type> operator + (Vec3D<Type> v);
	const Vec3D<Type>& operator += (const Vec3D<Type>& v);
	
	Vec3D<Type> operator - () const;
	Vec3D<Type> operator - (Vec3D<Type> v);
	const Vec3D<Type>& operator -= (Vec3D<Type> v);
	
	Type operator * (const Vec3D<Type>& v) const;
	Vec3D<Type> operator * (Type value) const;
	const Vec3D<Type>& operator *= (Type value);
	
	const Vec3D<Type>& operator /= (Type value);
	
	Vec3D<Type> inv() const;
	
	Vec3D<Type> operator ^(double exponent) const;
	
	Vec3D<Type> f(Type (*func)(Type)) const;
	
	Type sum() const;
	Type norm() const;
	
	bool operator == (const Vec3D<Type>& v) const;
	
	std::ostream & print(std::ostream &os) const;
};

template<class Type>
std::ostream& operator << (std::ostream& os,const Vec3D<Type> & v);

template<class Type>
Vec3D<Type> operator * (Type value, const Vec3D<Type> v);


#include "Vec3D.tpp"

#endif
