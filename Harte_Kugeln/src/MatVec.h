#ifndef SRC_MATVEC_H_
#define SRC_MATVEC_H_

#include <vector>
#include <ostream>

template<typename ElementType, unsigned DIM>
class MatVec {
private:
	std::vector<ElementType> m_vec;
public:
  MatVec() : m_vec(DIM, ElementType{}) {}
  MatVec(ElementType element) : m_vec(DIM, element) {}
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
	std::cout << "MatVecSwap" << '\n';
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

};

template<typename T, unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MatVec<T,DIM>& vec) {
	return vec.print(os);
}

template<typename T1, typename T2, unsigned DIM>
auto operator* (const MatVec<T1, DIM>& vec1, const MatVec<T2, DIM>& vec2) -> MatVec<decltype( T1{} * T2{} ), DIM> {
	  MatVec<decltype( T1{} * T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = vec1[i] * vec2[i];
	  return result;
}

#endif /* SRC_MATVEC_H_ */
