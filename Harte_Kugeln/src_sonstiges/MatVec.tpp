
template<typename ElementType, unsigned DIM>
inline void MatVec<ElementType, DIM>::neg() {
	for (auto& el : m_vec)
		el = -el;
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>::MatVec(MatVec<ElementType, DIM> && mec) :
		MatVec { } {
	swap(*this, mec);
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>::MatVec(const MatVec<ElementType, DIM>& mec) :
		m_vec { } {
	for (unsigned i = 0; i < DIM; ++i)
		m_vec[i] = mec.m_vec[i];
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>::MatVec(std::initializer_list<ElementType> args) :
		MatVec { } {
	auto begin = args.begin(), end = args.end();
	auto vbegin = m_vec.begin(), vend = m_vec.end();
	for (; begin != end && vbegin != vend; ++begin, ++vbegin)
		*vbegin = *begin;
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>::MatVec(ElementType element) :
		m_vec{} {
	m_vec.fill(element);
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>::MatVec() :
		m_vec{} {
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>::~MatVec() {
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>& MatVec<ElementType, DIM>::operator =(
		MatVec<ElementType, DIM> && mec) {
	swap(*this, mec);
	return *this;
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>& MatVec<ElementType, DIM>::operator =(
		const MatVec<ElementType, DIM>& mec) {
	m_vec = mec.m_vec;
	return *this;
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
inline auto MatVec<ElementType, DIM>::begin() -> decltype(m_vec.begin()) {
	return m_vec.begin();
}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::end() -> decltype(m_vec.end()) {
	return m_vec.end();
}

template<typename ElementType, unsigned DIM>
inline std::ostream& MatVec<ElementType, DIM>::print(std::ostream& os) const {
	for (auto& el : m_vec)
		os << el << ", ";
	return os;
}

template<typename ElementType, unsigned DIM>
inline bool MatVec<ElementType, DIM>::operator ==(
		const MatVec<ElementType, DIM>& other) const {
	return m_vec == other.m_vec;
}

template<typename ElementType, unsigned DIM>
inline bool MatVec<ElementType, DIM>::operator !=(
		const MatVec<ElementType, DIM>& other) const {
	return !operator ==(other);
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM>& MatVec<ElementType, DIM>::operator +=(
		const MatVec<ElementType, DIM>& vec2) {
	for (unsigned i = 0; i < DIM; ++i)
		m_vec[i] = m_vec[i] + vec2[i];
	return *this;
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM> MatVec<ElementType, DIM>::operator +(
		const MatVec<ElementType, DIM>& vec2) const {
	MatVec<ElementType, DIM> result { *this };
		result += vec2;
	return result;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
auto MatVec<ElementType, DIM>::operator+ (const T2& s) const -> MatVec<decltype( ElementType{} + T2{} ), DIM>  {
	  MatVec<decltype( ElementType{} + T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = m_vec[i] + s;
	  return result;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
inline auto MatVec<ElementType, DIM>::operator -(
		const MatVec<T2, DIM>& vec2) const -> MatVec<decltype(ElementType {}- T2 {}),DIM> {
	MatVec<decltype(ElementType {}- T2 {}), DIM> result { };
	for (unsigned i = 0; i < DIM; ++i)
		result[i] = m_vec[i] - vec2[i];
	return result;
}

template<typename ElementType, unsigned DIM>
inline MatVec<ElementType,DIM>& MatVec<ElementType, DIM>::operator -=(
		const MatVec<ElementType, DIM>& vec2) {
	for (unsigned i = 0; i < DIM; ++i)
		m_vec[i] = m_vec[i] - vec2[i];
	return *this;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
inline auto MatVec<ElementType, DIM>::operator- (const T2& s) const -> MatVec<decltype( ElementType{} - T2{} ), DIM>  {
	  MatVec<decltype( ElementType{} - T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = m_vec[i] - s;
	  return result;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
inline auto MatVec<ElementType, DIM>::operator* (const MatVec<T2, DIM>& vec2) const -> decltype( ElementType{} * T2{} )  {
	  decltype( ElementType{} * T2{} ) result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result += m_vec[i] * vec2[i];
	  return result;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
inline auto MatVec<ElementType, DIM>::operator* (const T2& s) const -> MatVec<decltype( ElementType{} * T2{} ), DIM>  {
	  MatVec<decltype( ElementType{} * T2{} ), DIM> result{};
	  for (unsigned i=0; i<DIM; ++i)
		  result[i] = m_vec[i] * s;
	  return result;
}

template<typename ElementType, unsigned DIM>
template<typename T2>
inline auto MatVec<ElementType, DIM>::operator/ (const T2& s) const -> MatVec<decltype( ElementType{} / T2{} ), DIM>  {
	  MatVec<decltype( ElementType{} / T2{} ), DIM> result{};
	  auto inv = 1.0 / s;
	  return operator*(inv);
}


template<typename ElementType, unsigned DIM>
inline MatVec<ElementType, DIM> MatVec<ElementType, DIM>::operator- () const {
	MatVec<ElementType, DIM> result{*this};
	result.neg();
	return result;
}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::norm2() const -> decltype(ElementType {}* ElementType {}) {
	decltype(ElementType {}* ElementType {}) sum { };
	for (auto& el : m_vec)
		sum += el * el;
	return sum;
}

template<typename ElementType, unsigned DIM>
inline auto MatVec<ElementType, DIM>::norm() const -> decltype(ElementType {}) {
	return sqrt(norm2());
}
