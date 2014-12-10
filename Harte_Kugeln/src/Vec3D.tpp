#include <ostream>
#include <cmath>
#include <vector>

using namespace std;

template<class Type>
const Vec3D<Type>& Vec3D<Type>::add(const Vec3D<Type>& v) {
	for (int i=0; i<3; ++i) m_vec[i] += v.m_vec[i];
	return *this;
}
template<class Type>
const Vec3D<Type>& Vec3D<Type>::make_negative() {
	for (int i=0; i<3; ++i) m_vec[i] = - m_vec[i];
	return *this;
}

template<class Type>
Vec3D<Type>::Vec3D(Type a, Type b, Type c) : m_vec{a,b,c} {}

template<class Type>
Vec3D<Type>::Vec3D(const Type * array) : m_vec{array[0],array[1],array[2]} {}

template<class Type>
Vec3D<Type>::Vec3D(const Vec3D<Type> & v) : Vec3D<Type>() {
	std::copy(v.m_vec, v.m_vec + 3, m_vec);
}

template<class Type>
Vec3D<Type>::Vec3D(Vec3D<Type>&& v) { swap( *this, v); }

template<class Type>
Type& Vec3D<Type>::operator [] (int i) { return m_vec[i]; }

template<class Type>
const Type& Vec3D<Type>::operator [] (int i) const { return m_vec[i]; }

template<class Type>
const Vec3D<Type>& Vec3D<Type>::operator = (Vec3D<Type> v) {
	swap(*this,v);
	return *this;
}

template<class Type>
Vec3D<Type> Vec3D<Type>::operator + (Vec3D<Type> v) {
	v.add(*this);
	return v;
}

template<class Type>
const Vec3D<Type>& Vec3D<Type>::operator += (const Vec3D<Type>& v) {
	return add(v);
}

template<class Type>
Vec3D<Type> Vec3D<Type>::operator - (Vec3D<Type> v) {
	v.make_negative();
	v.add(*this);
	return v;
}

template<class Type>
const Vec3D<Type>& Vec3D<Type>::operator -= (Vec3D<Type> v) {
	v.make_negative();
	return add(v);
}	

template<class Type>
Vec3D<Type> Vec3D<Type>::operator - () const{
	Vec3D<Type> v{*this};
	return v.make_negative();
}

template<class Type>
Type Vec3D<Type>::operator * (const Vec3D<Type>& v) const {
	Type re{};
	for (int i=0; i<3; ++i) re += m_vec[i] * v.m_vec[i];
	return re;
}

template<class Type>
Vec3D<Type> Vec3D<Type>::operator * (Type value) const {
	Vec3D<Type> v{*this};
	for (int i=0; i<3; ++i) v.m_vec[i] *= value;
	return v;
}

template<class Type>
const Vec3D<Type>& Vec3D<Type>::operator *= (Type value) {
	for (int i=0; i<3; ++i) m_vec[i] *= value;
	return *this;
}

template<class Type>
const Vec3D<Type>& Vec3D<Type>::operator /= (Type value) {
	Type one{};
	++one;
	value = one / value;
	return *this *= value;
}

template<class Type>
Vec3D<Type> Vec3D<Type>::inv() const {
	Vec3D<Type> v{*this};
	Type one{};
	++one;
	
	for (int i=0; i<3; ++i) v.m_vec[i] = one/v.m_vec[i];
	return v;
}

template<class Type>
Vec3D<Type> Vec3D<Type>::operator ^(double exponent) const {
	Vec3D<Type> v{*this};
	for (int i=0; i<3; ++i) v.m_vec[i] = pow(v.m_vec[i],exponent);
	return v;
}

template<class Type>
Vec3D<Type> Vec3D<Type>::f(Type (*func)(Type)) const {
	Vec3D<Type> v{*this};
	for (int i=0; i<3; ++i) v.m_vec[i] = func( v.m_vec[i] );
	return v;
}

template<class Type>
Type Vec3D<Type>::sum() const {
	Type s{};
	for (int i=0; i<3; ++i) s += m_vec[i];
	return s;
}

template<class Type>
Type Vec3D<Type>::norm() const {
	Type s{};
	for (int i=0; i<3; ++i) s += m_vec[i] * m_vec[i];
	return sqrt(s);
}

template<class Type>
bool Vec3D<Type>::operator == (const Vec3D<Type>& v) const {
	bool re = true;
	for (int i=0; i<3; ++i) re = re && ( m_vec[i] == v.m_vec[i] );
	return re;
}

template<class Type>
std::ostream & Vec3D<Type>::print(ostream &os) const {
	for (int i=0; i<3; ++i) os << m_vec[i] << " ";
	return os;
}


template<class Type>
std::ostream& operator << (std::ostream& os,const Vec3D<Type>& v) {return v.print(os);}

template<class Type>
Vec3D<Type> operator * (Type value, const Vec3D<Type> v) {return v * value;}
