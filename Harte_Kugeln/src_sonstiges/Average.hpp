#ifndef AVERAGE_HPP_
#define AVERAGE_HPP_

template<class T>
struct Average {
	using ElementT = T;

	Average() = default;
	explicit Average(const ElementT& val) : m_value{val}, count{} { }
	Average(const Average& other) = default;
	Average(Average&& other) = default;
	~Average() { }

	Average& operator =(const Average& other) = default;
	Average& operator =(Average&& other) = default;


	operator ElementT() const{
		return this->result();
	}

	void operator ()(const ElementT& el) {
		m_value = m_value + el;
		++count;
	}

	ElementT value() const {
		return this->result();
	}

private:
	ElementT m_value;
	size_t count;

	ElementT result() const {
		return m_value * (1./count);
	}
};

using dAverage = Average<double>;

#endif // AVERAGE_HPP_
