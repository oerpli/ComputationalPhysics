#include <iostream>
#include <vector>
#include <algorithm>
//Bin noch nicht so vertraut mit Units, hab einfach mal einige reingeladen...
#include <boost/units/cmath.hpp>
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>


using namespace std;
using namespace boost::units;
using namespace boost::units::si;

template<typename T1, typename T2>
auto operator+ (const vector<T1>& v1, const vector<T2>& v2) -> vector<decltype( T1{} + T2{} )> {
	vector< decltype( T1{} + T2{} ) > res( min(v1.size(), v2.size() ), 0);
	for (unsigned i=0; i<res.size(); ++i)
		res[i] = v1[i] + v2[i];
	return res;
}

template<typename T1, typename T2>
auto operator* (const vector<T1>& v, const quantity<T2> & s) -> vector<decltype( T1{} * s )> {
	vector< decltype( T1{} * s ) > res( v.size(), 0);
	for (unsigned i=0; i<res.size(); ++i)
		res[i] = v[i] * s;
	return res;
}

template<typename T1>
auto operator* (const vector<T1>& v, double s) -> vector<decltype( T1{} * s )> {
	vector< decltype( T1{} * s ) > res( v.size(), 0);
	for (unsigned i=0; i<res.size(); ++i)
		res[i] = v[i] * s;
	return res;
}

template<typename T1, typename T2>
auto operator* (const vector<T1>& v1, const vector<T2>& v2) -> decltype( T1{} * T2{} ) {
	decltype( T1{} * T2{} ) res=0;
	auto size = min( v1.size(), v2.size() );

	for (unsigned i=0; i<size; ++i)
		res += v1[i] * v2[i];
	return res;
}


int main() {

	force	N = newton;
	length	m = meter;

	quantity<force> F1(3*N);
	quantity<length> l1(5*m);
	auto E1(5*joule);

	cout << "F1: " << F1 << '\n';
	cout << "l1: " << l1 << '\n';
	cout << "E1: " << E1 << '\n';
	cout << "F1*l1-E1: " << F1 * l1 - E1 << '\n';


	std::vector< quantity<length> >  vec_length(3);
	vec_length[0] = l1;
	vec_length[1] = 2 * m;
	vec_length[2] = 10 * m;

	std::vector< quantity<force> >  vec_newton(3);
	for(unsigned i=0; i<vec_newton.size(); ++i)
		vec_newton[i] = 2 * i * newton;

	cout << "Newton Vector:\n";
	for(auto& el : vec_newton) cout << el << '\n';

	cout << "Newton Vector * 5m:\n";
	quantity<length> scalar = 5 * m;
	auto vec_newton2 = vec_newton * scalar;
	for(auto& el : vec_newton2) cout << el << '\n';

	cout << "Length Vector:\n";
	for(auto& el : vec_length) cout << el << '\n';

	cout << "Newton Vec * Length Vec: ";
	cout << vec_newton * vec_length << '\n';

}
