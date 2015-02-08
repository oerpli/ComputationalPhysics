template<class ElementT>
void Autocorrelation<ElementT>::add(const ElementT& el) {
	m_queue.add(el);

	const auto q0 = *(m_queue.begin());
	const auto end_q = m_queue.cend();
	auto iter_av = m_vec_av.begin();

	for (auto iter_q = m_queue.cbegin(); iter_q != end_q; ++iter_av, ++iter_q)
		iter_av->add(  q0 * (*iter_q) );

	this->reset_iterator();
}

template<class ElementT>
std::pair<typename Autocorrelation<ElementT>::return_type, bool>
	Autocorrelation<ElementT>::get_value_pair() {
	if ( (long) m_queue.size() <= m_result_iter - m_vec_av.begin() )
		return std::pair<return_type, bool> (return_type{}, false);

	auto result = m_result_iter++;
	return std::pair<return_type, bool> (result->value(), true);
}

template<class ElementT>
inline void Autocorrelation<ElementT>::reset_iterator() {
	if ( m_result_iter != m_vec_av.begin() ) m_result_iter = m_vec_av.begin();
}
