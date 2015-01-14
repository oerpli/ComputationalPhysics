
template<typename ElementType, unsigned DIM>
void MatVec<ElementType, DIM>::neg() {
	for (auto& el : m_vec)
		el = -el;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM>::MatVec(std::initializer_list<ElementType> args) :
		MatVec { } {
	auto begin = args.begin(), end = args.end();
	auto vbegin = m_vec.begin(), vend = m_vec.end();
	for (; begin != end && vbegin != vend; ++begin, ++vbegin)
		*vbegin = *begin;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM>::MatVec(ElementType element) :m_vec{} {
	m_vec.fill(element);
}

template<typename ElementType, unsigned DIM>
inline const ElementType& MatVec<ElementType, DIM>::operator [](int i) const {
	return m_vec[i];
}

template<typename ElementType, unsigned DIM>
inline ElementType& MatVec<ElementType, DIM>::operator [](int i) {
	return m_vec[i];
}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::begin() {return m_vec.begin();}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::cbegin() {return m_vec.cbegin();}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::end() {return m_vec.end();}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::cend() {return m_vec.cend();}

template<typename ElementType, unsigned DIM>
inline bool MatVec<ElementType, DIM>::operator ==(const MatVec<ElementType, DIM>& other) const {
	return m_vec == other.m_vec;
}

template<typename ElementType, unsigned DIM>
inline bool MatVec<ElementType, DIM>::operator !=(
		const MatVec<ElementType, DIM>& other) const {
	return !operator ==(other);
}


template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM> MatVec<ElementType, DIM>::operator +(
		const MatVec<ElementType, DIM>& vec2) const {
	MatVec<ElementType, DIM> result { *this };
		result += vec2;
	return result;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM>& MatVec<ElementType, DIM>::operator +=(
		const MatVec<ElementType, DIM>& vec2) {
	for (unsigned i = 0; i < DIM; ++i)
		m_vec[i] = m_vec[i] + vec2[i];
	return *this;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM> MatVec<ElementType, DIM>::operator +(const ElementType& s) const {
	  MatVec<ElementType, DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = m_vec[i] + s;
	  return result;
}


template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM> MatVec<ElementType, DIM>::operator -(const MatVec<ElementType, DIM>& vec2) const {
	MatVec<ElementType, DIM> result { };
	for (unsigned i = 0; i < DIM; ++i)
		result[i] = m_vec[i] - vec2[i];
	return result;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType,DIM>& MatVec<ElementType, DIM>::operator -=(
		const MatVec<ElementType, DIM>& vec2) {
	for (unsigned i = 0; i < DIM; ++i)
		m_vec[i] = m_vec[i] - vec2[i];
	return *this;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM> MatVec<ElementType, DIM>::operator -(const ElementType& s) const {
	  MatVec<ElementType, DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = m_vec[i] - s;
	  return result;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM>&  MatVec<ElementType, DIM>::operator -=(const ElementType& s) {
	for (auto& el : m_vec) el -= s;
	return *this;
}

template<typename ElementType, unsigned DIM>
MatVec<ElementType, DIM> MatVec<ElementType, DIM>::operator -() const {
	MatVec<ElementType, DIM> result{*this};
	result.neg();
	return result;
}


template<typename ElementType, unsigned DIM>
template<typename T2>
auto MatVec<ElementType, DIM>::operator *(const MatVec<T2, DIM>& vec2) const {
	  decltype( ElementType{} * T2{} ) result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result += m_vec[i] * vec2[i];
	  return result;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
auto MatVec<ElementType, DIM>::operator *(const T2& s) const {
	  MatVec<decltype( ElementType{} * T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = m_vec[i] * s;
	  return result;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
auto MatVec<ElementType, DIM>::operator %(const MatVec<T2, DIM>& other) const{
	MatVec<decltype( ElementType{} * T2{} ), DIM> result {};
	for (unsigned i = 0; i < DIM; ++i)
		result[i] = m_vec[i] * other[i];
	return result;
}


template<typename ElementType, unsigned DIM>
template<typename T2>
auto MatVec<ElementType, DIM>::operator /(const T2& s) const {
	  MatVec<decltype( ElementType{} / T2{} ), DIM> result{};
	  if (s == T2{})
		  return MatVec<decltype( ElementType{} / T2{} ), DIM>
	  	  	  {std::numeric_limits<decltype( ElementType{} / T2{} )>::max() };
	  return operator*(1.0 / s);
}

template<typename ElementType, unsigned DIM>
template<typename T2>
auto MatVec<ElementType, DIM>::operator /(const MatVec<T2, DIM>& other) const {
	MatVec<decltype( ElementType{} / T2{} ), DIM> result {};
	for (unsigned i = 0; i < DIM; ++i) {
		if (other[i] == T2{})
			result[i] = std::numeric_limits<decltype( ElementType{} / T2{} )>::max();
		else result[i] = m_vec[i] / other[i];
	}
	return result;
}


template<typename ElementType, unsigned DIM>
auto MatVec<ElementType, DIM>::norm2() const {
	decltype(ElementType {}* ElementType {}) sum { };
	for (auto& el : m_vec)
		sum += el * el;
	return sum;
}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::norm() const {
	return sqrt(this->norm2());
}

template<typename ElementType, unsigned DIM>
std::ostream& MatVec<ElementType, DIM>::print(std::ostream& os) const {
	for (auto& el : m_vec)
		os << el << ", ";
	return os;
}

template<typename T, unsigned DIM>
std::ostream& operator<< (std::ostream& os, const MatVec<T,DIM>& vec) {
	return vec.print(os);
}

template<typename T, unsigned DIM>
MatVec<T,DIM> floor(MatVec<T,DIM> mec) {
	mec([&] (T& el) {el = floor(el); });
	return mec;
}

template<typename T, unsigned DIM>
MatVec<T,DIM> round(MatVec<T,DIM> mec) {
	mec([&] (T& el) {el = round(el); });
	return mec;
}

//non class functions

