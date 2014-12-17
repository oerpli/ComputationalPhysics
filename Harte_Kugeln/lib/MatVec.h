#ifndef SRC_MATVEC_H_
#define SRC_MATVEC_H_

#include <vector>
#include <ostream>
#include <initializer_list>

template<typename ElementType, unsigned DIM>
class MatVec {
private:
	std::vector<ElementType> m_vec;

  // make negative
  void neg() { for (auto& el : m_vec) el = -el; }
public:
  MatVec() : m_vec(DIM, ElementType{}) {}
  MatVec(ElementType element) : m_vec(DIM, element) {}
  MatVec(std::initializer_list<ElementType> args) : MatVec{} {
	  auto begin = args.begin(), end = args.end();
	  auto vbegin = m_vec.begin(), vend = m_vec.end();

	  for (; begin != end && vbegin != vend; ++begin, ++vbegin) {
		  *vbegin = *begin;
	  }
	  for (; vbegin != vend; ++vbegin) {
		  *vbegin = ElementType{};
	  }
  }
  MatVec(const MatVec<ElementType, DIM>& mec) : m_vec{mec.m_vec} {}
  MatVec(MatVec<ElementType, DIM>&& mec) : MatVec{} { swap(*this, mec); }
  virtual ~MatVec() {}

  MatVec<ElementType, DIM>& operator= (const MatVec<ElementType, DIM>& mec) {
	  m_vec = mec.m_vec;
	  return *this;
  }

  MatVec<ElementType, DIM>& operator= (MatVec<ElementType, DIM>&& mec) {
	  swap(*this, mec);
	  return *this;
  }

  friend void swap(MatVec<ElementType, DIM>& meca, MatVec<ElementType, DIM>& mecb) {
	std::swap(meca.m_vec, mecb.m_vec);
  }

  //Zugriff wie auf Array: matvec[i]
  ElementType& operator [] (int i) { return m_vec[i]; }
  const ElementType& operator [] (int i) const { return m_vec[i]; }

  //Erlaubt iteration durch Vektor und daher range based for
  auto begin() -> decltype( m_vec.begin() ) { return m_vec.begin(); }
  auto end() -> decltype( m_vec.end() ) { return m_vec.end(); }

  //Für overload << von aussen
  std::ostream& print(std::ostream& os) const {
		for (auto& el : m_vec) os << el << ", ";
		return os;
  }

  bool operator== (const MatVec<ElementType, DIM>& other) const {
	  return m_vec == other.m_vec;
  }

  // Vektoraddition
  template<typename T2>
  auto operator+ (const MatVec<T2, DIM>& vec2) const -> MatVec<decltype( ElementType{} + T2{} ), DIM>  {
  	  MatVec<decltype( ElementType{} + T2{} ), DIM> result{};
  	  for (unsigned i=0; i<DIM; ++i)
  		  result[i] = m_vec[i] + vec2[i];
  	  return result;
  }

  // Addition jedes Elements mit Skalar
  template<typename T2>
  auto operator+ (const T2& s) const -> MatVec<decltype( ElementType{} + T2{} ), DIM>  {
  	  MatVec<decltype( ElementType{} + T2{} ), DIM> result{};
  	  for (unsigned i=0; i<DIM; ++i)
  		  result[i] = m_vec[i] + s;
  	  return result;
  }

  // Vektorsubtraktion
  template<typename T2>
  auto operator- (const MatVec<T2, DIM>& vec2) const -> MatVec<decltype( ElementType{} - T2{} ), DIM>  {
  	  MatVec<decltype( ElementType{} - T2{} ), DIM> result{};
  	  for (unsigned i=0; i<DIM; ++i)
  		  result[i] = m_vec[i] - vec2[i];
  	  return result;
  }

  // Subtraktion jedes Elements mit Skalar
  template<typename T2>
  auto operator- (const T2& s) const -> MatVec<decltype( ElementType{} - T2{} ), DIM>  {
  	  MatVec<decltype( ElementType{} - T2{} ), DIM> result{};
  	  for (unsigned i=0; i<DIM; ++i)
  		  result[i] = m_vec[i] - s;
  	  return result;
  }

  // Skalarprodukt
  template<typename T2>
  auto operator* (const MatVec<T2, DIM>& vec2) const -> decltype( ElementType{} * T2{} )  {
  	  decltype( ElementType{} * T2{} ) result{};
  	  for (unsigned i=0; i<DIM; ++i)
  		  result += m_vec[i] * vec2[i];
  	  return result;
  }

  // Multiplikation mit Skalar
  template<typename T2>
  auto operator* (const T2& s) const -> MatVec<decltype( ElementType{} * T2{} ), DIM>  {
	  MatVec<decltype( ElementType{} * T2{} ), DIM> result{};
  	  for (unsigned i=0; i<DIM; ++i)
  		  result[i] = m_vec[i] * s;
  	  return result;
  }

  // Division durch Skalar
  template<typename T2>
  auto operator/ (const T2& s) const -> MatVec<decltype( ElementType{} / T2{} ), DIM>  {
	  MatVec<decltype( ElementType{} / T2{} ), DIM> result{};
	  auto inv = 1.0 / s;
  	  return operator*(inv);
  }


  // return negative vector
  MatVec<ElementType, DIM> operator- () const {
	MatVec<ElementType, DIM> result{*this};
	result.neg();
	return result;
  }

  /*
  // Vektorprodukt wie in Scilab vec1.*vec2
  template<typename T2>
  auto operator* (const MatVec<T2, DIM>& vec2) const -> MatVec<decltype( ElementType{} * T2{} ), DIM>  {
  	  MatVec<decltype( ElementType{} * T2{} ), DIM> result{};
  	  for (unsigned i=0; i<DIM; ++i)
  		  result[i] = m_vec[i] * vec2[i];
  	  return result;
  }
  */

  auto norm2() const -> decltype(ElementType{} * ElementType{}) {
	  decltype(ElementType{} * ElementType{}) sum{};
	  for (auto& el : m_vec) sum += el * el;
	  return sum;
  }

  auto norm() const -> decltype(ElementType{}) {
	  return sqrt( norm2() );
  }
};

template<typename T, unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MatVec<T,DIM>& vec) {
	return vec.print(os);
}
/*
template<typename T1, typename T2, unsigned DIM>
auto operator* (const MatVec<T1, DIM>& vec1, const MatVec<T2, DIM>& vec2) -> MatVec<decltype( T1{} * T2{} ), DIM> {
	  MatVec<decltype( T1{} * T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = vec1[i] * vec2[i];
	  return result;
}
*/
#endif /* SRC_MATVEC_H_ */
