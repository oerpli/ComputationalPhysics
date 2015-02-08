#ifndef SRC_SONSTIGES_VECTOR_QUEUE_HPP_
#define SRC_SONSTIGES_VECTOR_QUEUE_HPP_

#include <cstddef>
#include <memory>
#include <vector>
#include <type_traits>

template<class ElementT>
struct Vector_Queue {
	using value_type = ElementT;

	explicit Vector_Queue(size_t size) : max_size { size }, m_queue { } {
		m_queue.reserve(max_size);
	}

	explicit Vector_Queue(const std::vector<ElementT>& vec) :
			max_size{ vec.size() }, m_queue{vec} {}

	Vector_Queue(const Vector_Queue& other) = default;
	Vector_Queue(Vector_Queue&& other) = default;
	~Vector_Queue() = default;

	Vector_Queue& operator =(const Vector_Queue& other) = default;
	Vector_Queue& operator =(Vector_Queue&& other) = default;


	// vector operations

	auto size() const;
	auto capacity() const;

	ElementT& operator [](size_t i);
	const ElementT& operator [](size_t i) const;

	auto begin() const;
	auto cbegin() const;

	auto end() const;
	auto cend() const;

	// queue operations

	template<class Container>
	bool operator ==(const Container& contain) const;

	template<class Container>
	bool operator !=(const Container& contain) const;

	void add(ElementT el);

private:
	size_t max_size;
	std::vector<ElementT> m_queue;

	void move_elements(ElementT&& el);
};

#include "Vector_Queue.tpp"

#endif /* SRC_SONSTIGES_VECTOR_QUEUE_HPP_ */
