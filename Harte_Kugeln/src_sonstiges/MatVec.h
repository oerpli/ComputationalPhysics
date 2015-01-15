#ifndef SRC_MATVEC_H_
#define SRC_MATVEC_H_

#include <limits>

#include <array>
#include <ostream>
#include <initializer_list>

#include "units_typedef.h"

template<typename ElementType, unsigned DIM>
class MatVec {
private:
	typedef MatVec<ElementType, DIM> self_t;

	std::array<ElementType, DIM> m_vec;

  // make negative
	void neg();
public:
	MatVec() = default;
	explicit MatVec(ElementType element);
	MatVec(std::initializer_list<ElementType> args);
	MatVec(const self_t& mec) = default;
	MatVec(self_t&& mec) = default;
	~MatVec() = default;

	self_t& operator =(const self_t& mec) = default;
	self_t& operator =(self_t && mec) = default;

	friend void swap(self_t& meca, self_t& mecb) {
		std::swap(meca.m_vec, mecb.m_vec);
	}

	//Zugriff wie auf Array: matvec[i]
	ElementType& operator [](int i);
	const ElementType& operator [](int i) const;

	//Erlaubt iteration durch Vektor und daher range based for
	auto begin();
	auto cbegin();

	auto end();
	auto cend();

	//Für overload << von aussen
	std::ostream& print(std::ostream& os) const;

	bool operator ==(const self_t& other) const;
	bool operator !=(const self_t& other) const;


	// Vektoraddition
	self_t operator +(const self_t& vec2) const;
	self_t& operator +=(const self_t& vec2);

	// Addition jedes Elements mit Skalar
	self_t operator +(const ElementType& s) const;

	// Vektorsubtraktion
	self_t operator -(const self_t& vec2) const;
	self_t& operator -=(const self_t& vec2);

	// Subtraktion jedes Elements mit Skalar
	self_t operator -(const ElementType& s) const;
	self_t&  operator -=(const ElementType& s);

	// return negative vector
	self_t operator -() const;


	// Skalarprodukt
	template<typename T2>
	auto operator *(const MatVec<T2, DIM>& vec2) const;

	// Multiplikation mit Skalar
	template<typename T2>
	auto operator *(const T2& s) const;

	// Multiplikation zwei Vektoren elementweise
	template<typename T2>
	auto operator %(const MatVec<T2, DIM>& other) const;


	// Division durch Skalar
	template<typename T2>
	auto operator /(const T2& s) const;

	// Division zwei Vektoren elementweise
	template<typename T2>
	auto operator /(const MatVec<T2, DIM>& other) const;


	auto norm2() const;
	auto norm() const;

	template<class UnaryFunction>
	UnaryFunction operator()(UnaryFunction f) {
		for (auto& el : m_vec) f( el );
		return f;
	}
};


template<typename T, unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MatVec<T,DIM>& vec);

template<typename T, unsigned DIM>
MatVec<T,DIM> floor(MatVec<T,DIM> mec);

template<typename T, unsigned DIM>
MatVec<T,DIM> round(MatVec<T,DIM> mec);

template<typename T, unsigned DIM>
T min(MatVec<T,DIM> mec);

#include "MatVec.tpp"

#endif /* SRC_MATVEC_H_ */
