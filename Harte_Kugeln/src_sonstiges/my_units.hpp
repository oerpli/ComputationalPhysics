#ifndef MY_UNITS_HPP_
#define MY_UNITS_HPP_

#include <utility>
#include <ostream>
#include <cmath>

template<int M, int L, int T>
class Quantity
{
public:
	constexpr Quantity(double val=0.0) : m_value{val} {}
	constexpr Quantity(const Quantity& x) : m_value{x.m_value} {}

	Quantity& operator+=(const Quantity& rhs)
    {
        m_value+=rhs.m_value;
        return *this;
    }

    Quantity& operator-=(const Quantity& rhs)
    {
        m_value-=rhs.m_value;
        return *this;
    }

    constexpr Quantity operator -() {
    	return Quantity<M,L,T>(-m_value);
    }

    constexpr  double Convert(const Quantity& rhs)
    {
        return m_value/rhs.m_value;
    }

    constexpr  double getValue() const
    {
        return m_value;
    }

    constexpr operator double()
	{
    	return this->getValue();
	}

private:
    double m_value;
};

template <int M, int L, int T>
constexpr Quantity<M,L,T> operator+(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return Quantity<M,L,T>(lhs)+=rhs;
}

template <int M, int L, int T>
constexpr Quantity<M,L,T> operator-(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return Quantity<M,L,T>(lhs)-=rhs;
}

template <int M1, int L1, int T1, int M2, int L2, int T2>
constexpr Quantity<M1+M2,L1+L2,T1+T2> operator*(const Quantity<M1,L1,T1>& lhs, const Quantity<M2,L2,T2>& rhs)
{
    return Quantity<M1+M2,L1+L2,T1+T2>(lhs.getValue()*rhs.getValue());
}

template <int M, int L, int T>
constexpr Quantity<M,L,T> operator*(const double& lhs, const Quantity<M,L,T>& rhs)
{
    return Quantity<M,L,T>(lhs*rhs.getValue());
}

template <int M, int L, int T>
constexpr Quantity<M,L,T> operator*(const Quantity<M,L,T>& lhs, const double& rhs)
{
    return rhs * lhs;
}

template <int M1, int L1, int T1, int M2, int L2, int T2>
constexpr Quantity<M1-M2,L1-L2,T1-T2> operator/(const Quantity<M1,L1,T1>& lhs,
            const Quantity<M2,L2,T2>& rhs)
{
    return Quantity<M1-M2,L1-L2,T1-T2>(lhs.getValue()/rhs.getValue());
}

template <int M, int L, int T>
constexpr Quantity<-M, -L, -T> operator/(const double& x, const Quantity<M,L,T>& rhs)
{
    return Quantity<-M,-L,-T>(x/rhs.getValue());
}

template <int M, int L, int T>
constexpr Quantity<M, L, T> operator/(const Quantity<M,L,T>& rhs, const double& x)
{
    return Quantity<M,L,T>(rhs.getValue()/x);
}

template <int M, int L, int T>
constexpr bool operator==(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return (lhs.getValue()==rhs.getValue());
}

template <int M, int L, int T>
constexpr bool operator!=(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return (lhs.getValue()!=rhs.getValue());
}

template <int M, int L, int T>
constexpr bool operator<=(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()<=rhs.getValue();
}

template <int M, int L, int T>
constexpr bool operator>=(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()>=rhs.getValue();
}

template <int M, int L, int T>
constexpr bool operator< (const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()<rhs.getValue();
}

template <int M, int L, int T>
constexpr bool operator> (const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()>rhs.getValue();
}

template <int exp, int M, int L, int T>
constexpr Quantity<M*exp, L*exp, T*exp> unit_pow (const Quantity<M,L,T>& x)
{
    return Quantity<M*exp, L*exp, T*exp>( std::pow(x.getValue(), exp));
}

template <int M, int L, int T>
constexpr Quantity<M/2, L/2, T/2> sqrt(const Quantity<M,L,T>& x)
{
    return Quantity<M/2, L/2, T/2>( std::sqrt(x.getValue()) );
}

template<int M, int L, int T>
std::ostream& operator <<(std::ostream& os, const Quantity<M,L,T>& x)
{
	os << x.getValue();
	if (M != 0) os << " ME" << M;
	if (L != 0) os << " LE" << L;
	if (T != 0) os << " TE" << T;
	return os;
}


#endif // MY_UNITS_HPP_
