#include <iostream>
#include <vector>
#include <algorithm>
//Bin noch nicht so vertraut mit Units, hab einfach mal einige reingeladen...
#include <boost/units/cmath.hpp>
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/base.hpp>

#include <typeinfo>

//Klasse die den Vektor enthält
template<typename ElementType, unsigned DIM>
class MatVec {
private:
	std::vector<ElementType> m_vec;
public:
  MatVec() : m_vec(DIM, ElementType{}) {}
  MatVec(ElementType element) : m_vec(DIM, element) {}

  //Zugriff wie auf Array: matvec[i]
  ElementType& operator [] (int i) { return m_vec[i]; }
  const ElementType& operator [] (int i) const { return m_vec[i]; }

  auto begin() -> decltype( m_vec.begin() ) { return m_vec.begin(); }
  auto end() -> decltype( m_vec.end() ) { return m_vec.end(); }

  //Für overload << von aussen
  std::ostream& print(std::ostream& os) const {
		for (auto& el : m_vec) os << el << '\n';
		return os;
  }

};

using namespace std;
using namespace boost::units;
using namespace boost::units::si;

template<typename T, unsigned DIM>
ostream& operator<< (ostream& os, const MatVec<T,DIM>& vec) {
	return vec.print(os);
}


// Vectoren elementweise mulitiplizieren
// Scilab: vec1.*vec2
template<typename T1, typename T2, unsigned DIM>
auto operator* (const MatVec<T1, DIM>& vec1, const MatVec<T2, DIM>& vec2) -> MatVec<decltype( T1{} * T2{} ), DIM> {
	  MatVec<decltype( T1{} * T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = vec1[i] * vec2[i];
	  return result;
}

int main() {

	quantity<force> forceScalar = 3 * newton;
	MatVec<quantity<force>, 3> forceVec { forceScalar };
	quantity<length> lengthScalar = 3 * meter;
	MatVec<quantity<length>, 3> lengthVec { lengthScalar };

	forceVec[1] = 5 * newton;

	cout << forceVec << '\n';

	for (auto& el : lengthVec) cout << el << '\n';
	cout << '\n';

	auto flVec = forceVec * lengthVec;
	cout << flVec << '\n';


	MatVec<double,3> dVec { 3.1 };
	MatVec<int,3> iVec {3};


	cout << dVec * iVec << '\n';

}
