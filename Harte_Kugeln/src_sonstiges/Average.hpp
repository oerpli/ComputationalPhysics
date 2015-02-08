#ifndef AVERAGE_HPP_
#define AVERAGE_HPP_

template<class T>
struct Average {
	using value_type = T;

	Average() = default;
	explicit Average(const value_type& val) : m_value { val }, count { } { }

	Average(const Average& other) = default;
	Average(Average&& other) = default;
	~Average() { }

	Average& operator =(const Average& other) = default;
	Average& operator =(Average&& other) = default;

	void add(const value_type& el) {
		m_value = m_value + el;
		++count;
	}

	void operator ()(const value_type& el) { return this->add(el); }

	explicit operator value_type() const{ return this->result(); }

	value_type value() const { return this->result(); }

private:
	value_type m_value;
	size_t count;

	value_type result() const {
		if (! count) return value_type{};
		return m_value * (1. / count);
	}
};

#endif // AVERAGE_HPP_
