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

  //Zugriff wie auf Array: matvec[i]
  ElementType& operator [] (int i) { return m_vec[i]; }
  const ElementType& operator [] (int i) const { return m_vec[i]; }

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

#endif /* SRC_MATVEC_H_ */
