template<class ElementT>
inline auto Vector_Queue<ElementT>::size() const {
	return m_queue.size();
}

template<class ElementT>
inline auto Vector_Queue<ElementT>::capacity() const {
	return max_size;
}

template<class ElementT>
inline const ElementT& Vector_Queue<ElementT>::operator [](size_t i) const {
	return m_queue[i];
}

template<class ElementT>
inline ElementT& Vector_Queue<ElementT>::operator [](size_t i) {
	return m_queue[i];
}

template<class ElementT>
inline auto Vector_Queue<ElementT>::begin() const {
	return m_queue.begin();
}

template<class ElementT>
inline auto Vector_Queue<ElementT>::cbegin() const {
	return m_queue.cbegin();
}

template<class ElementT>
inline auto Vector_Queue<ElementT>::end() const {
	return m_queue.end();
}

template<class ElementT>
inline auto Vector_Queue<ElementT>::cend() const {
	return m_queue.cend();
}

template<class ElementT>
// queue operations
template<class Container>
bool Vector_Queue<ElementT>::operator ==(const Container& contain) const {

	auto beg_cont = std::begin(contain);
	const auto end_cont = std::end(contain);
	if (end_cont - beg_cont != (long) (m_queue.size()))
		return false;

	auto beg_q = m_queue.cbegin();
	bool flag { true };
	for (; beg_cont != end_cont && flag; ++beg_q, ++beg_cont)
		flag &= *beg_cont == *beg_q;
	return flag;
}

template<class ElementT>
template<class Container>
bool Vector_Queue<ElementT>::operator !=(const Container& contain) const {
	return !(this->operator ==(contain));
}

template<class ElementT>
void Vector_Queue<ElementT>::add(ElementT el) {
	if (m_queue.size() == max_size) {
		move_elements( std::move(el) );
	} else
		m_queue.push_back(std::move(el));
}

template<class ElementT>
void Vector_Queue<ElementT>::move_elements(ElementT&& el) {
	auto first = m_queue.begin(), second = m_queue.begin();
	const auto iter_end = m_queue.end();
	for (++first; first != iter_end; ++second, ++first)
		*second = std::move(*first);
	*second = std::move( el );
}

