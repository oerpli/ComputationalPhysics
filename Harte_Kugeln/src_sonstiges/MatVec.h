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
	void neg();
public:
	MatVec();
	MatVec(ElementType element);
	MatVec(std::initializer_list<ElementType> args);
	MatVec(const MatVec<ElementType, DIM>& mec);
	MatVec(MatVec<ElementType, DIM> && mec);
	virtual ~MatVec();

	MatVec<ElementType, DIM>& operator =(const MatVec<ElementType, DIM>& mec);

	MatVec<ElementType, DIM>& operator =(MatVec<ElementType, DIM> && mec);

	friend void swap(MatVec<ElementType, DIM>& meca, MatVec<ElementType, DIM>& mecb) {
		std::swap(meca.m_vec, mecb.m_vec);
	}

	//Zugriff wie auf Array: matvec[i]
	ElementType& operator [](int i);
	const ElementType& operator [](int i) const;

	//Erlaubt iteration durch Vektor und daher range based for
	auto begin() -> decltype(m_vec.begin());
	auto end() -> decltype(m_vec.end());

	//Für overload << von aussen
	std::ostream& print(std::ostream& os) const;

	bool operator ==(const MatVec<ElementType, DIM>& other) const;
	bool operator !=(const MatVec<ElementType, DIM>& other) const;

	// Vektoraddition
	MatVec<ElementType,DIM>& operator +=(
			const MatVec<ElementType, DIM>& vec2);

	MatVec<ElementType,DIM> operator +(
			const MatVec<ElementType, DIM>& vec2) const;

	// Addition jedes Elements mit Skalar
	template<typename T2>
	auto operator+ (const T2& s) const -> MatVec<decltype( ElementType{} + T2{} ), DIM>;

	// Vektorsubtraktion
	template<typename T2>
	auto operator -(
			const MatVec<T2, DIM>& vec2) const -> MatVec<decltype(ElementType {}- T2 {}),DIM>;

	// Subtraktion jedes Elements mit Skalar
	template<typename T2>
	auto operator- (const T2& s) const -> MatVec<decltype( ElementType{} - T2{} ), DIM>;

	// Skalarprodukt
	template<typename T2>
	auto operator* (const MatVec<T2, DIM>& vec2) const -> decltype( ElementType{} * T2{} );

	// Multiplikation mit Skalar
	template<typename T2>
	auto operator* (const T2& s) const -> MatVec<decltype( ElementType{} * T2{} ), DIM>;

	// Division durch Skalar
	template<typename T2>
	auto operator/ (const T2& s) const -> MatVec<decltype( ElementType{} / T2{} ), DIM>;


	// return negative vector
	MatVec<ElementType, DIM> operator- () const;

	auto norm2() const -> decltype(ElementType {}* ElementType {});
	auto norm() const -> decltype(ElementType {});
};

template<typename T, unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MatVec<T,DIM>& vec) {
	return vec.print(os);
}

#include "MatVec.tpp"

#endif /* SRC_MATVEC_H_ */