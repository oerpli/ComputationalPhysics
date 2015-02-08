#ifndef SRC_SONSTIGES_AUTOCORRELATION_HPP_
#define SRC_SONSTIGES_AUTOCORRELATION_HPP_

#include <vector>

#include "Average.hpp"
#include "Vector_Queue.hpp"

template<class ElementT>
struct Autocorrelation {
	using value_type = ElementT;
	using return_type = decltype(ElementT{} * ElementT{});

	explicit Autocorrelation(size_t size) : m_queue { size },
			m_vec_av(size), m_result_iter{} {}

	~Autocorrelation() = default;

	void add(const ElementT& el);

	std::pair<return_type, bool> get_value_pair();

	void reset_iterator();

private:
	Vector_Queue<ElementT> m_queue;
	std::vector<Average<return_type>> m_vec_av;
	typename std::vector<Average<return_type>>::iterator m_result_iter;
};

#include "Autocorrelation.tpp"

#endif /* SRC_SONSTIGES_AUTOCORRELATION_HPP_ */

