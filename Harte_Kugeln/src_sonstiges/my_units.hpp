#ifndef MY_UNITS_HPP_
#define MY_UNITS_HPP_

#include <utility>
#include <cmath>

#include "template_rational.hpp"

template<class M, class L, class T>
class Quantity
{
public:
	constexpr Quantity() = default;
	constexpr Quantity(const double& val) : m_value{val} {}
	constexpr Quantity(double&& val) : m_value{std::move(val)} {}
	constexpr Quantity(const Quantity& x) : m_value{x.m_value} {}
	constexpr Quantity(Quantity&& other) = default;

	Quantity& operator =(const Quantity& other) = default;
	Quantity& operator =(Quantity&& other) = default;

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

template <class M, class L, class T>
constexpr Quantity<M,L,T> operator+(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return Quantity<M,L,T>(lhs.getValue() + rhs.getValue());
}

template <class M, class L, class T>
constexpr Quantity<M,L,T> operator-(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return Quantity<M,L,T>(lhs.getValue() - rhs.getValue());
}

template <class M1, class L1, class T1, class M2, class L2, class T2>
constexpr Quantity<R_add<M1,M2>,R_add<L1,L2>,R_add<T1,T2>>
	operator*(const Quantity<M1,L1,T1>& lhs, const Quantity<M2,L2,T2>& rhs)
{
    return Quantity<R_add<M1,M2>,R_add<L1,L2>,R_add<T1,T2>>(lhs.getValue()*rhs.getValue());
}

template <class M, class L, class T>
constexpr Quantity<M,L,T> operator*(const double& lhs, const Quantity<M,L,T>& rhs)
{
    return Quantity<M,L,T>(lhs*rhs.getValue());
}

template <class M, class L, class T>
constexpr Quantity<M,L,T> operator*(const Quantity<M,L,T>& lhs, const double& rhs)
{
    return rhs * lhs;
}

template <class M1, class L1, class T1, class M2, class L2, class T2>
constexpr Quantity<R_sub<M1,M2>,R_sub<L1,L2>,R_sub<T1,T2>>
	operator/(const Quantity<M1,L1,T1>& lhs,
            const Quantity<M2,L2,T2>& rhs)
{
    return Quantity<R_sub<M1,M2>,R_sub<L1,L2>,R_sub<T1,T2>>(lhs.getValue()/rhs.getValue());
}

template <class M, class L, class T>
constexpr Quantity<R_neg<M>, R_neg<L>, R_neg<T>>
	operator/(const double& x, const Quantity<M,L,T>& rhs)
{
    return Quantity<R_neg<M>, R_neg<L>, R_neg<T>>(x/rhs.getValue());
}

template <class M, class L, class T>
constexpr Quantity<M, L, T> operator/(const Quantity<M,L,T>& rhs, const double& x)
{
    return Quantity<M,L,T>(rhs.getValue()/x);
}

template <class M, class L, class T>
constexpr bool operator==(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return (lhs.getValue()==rhs.getValue());
}

template <class M, class L, class T>
constexpr bool operator!=(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return (lhs.getValue()!=rhs.getValue());
}

template <class M, class L, class T>
constexpr bool operator<=(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()<=rhs.getValue();
}

template <class M, class L, class T>
constexpr bool operator>=(const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()>=rhs.getValue();
}

template <class M, class L, class T>
constexpr bool operator< (const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()<rhs.getValue();
}

template <class M, class L, class T>
constexpr bool operator> (const Quantity<M,L,T>& lhs, const Quantity<M,L,T>& rhs)
{
    return lhs.getValue()>rhs.getValue();
}

template <int exp_num, unsigned exp_den, class M, class L, class T>
constexpr Quantity<R_mul<M,Rational<exp_num,exp_den>>, R_mul<L,Rational<exp_num,exp_den>>, R_mul<T,Rational<exp_num,exp_den>>>
	unit_pow (const Quantity<M,L,T>& x)
{
    return Quantity<R_mul<M,Rational<exp_num,exp_den>>, R_mul<L,Rational<exp_num,exp_den>>, R_mul<T,Rational<exp_num,exp_den>>>
    		( std::pow(x.getValue(), double(exp_num)/exp_den));
}

template <class M, class L, class T>
constexpr Quantity<R_mul<M,Rational<1,2>>, R_mul<L,Rational<1,2>>, R_mul<T,Rational<1,2>>>
	sqrt(const Quantity<M,L,T>& x)
{
    return Quantity<R_mul<M,Rational<1,2>>, R_mul<L,Rational<1,2>>, R_mul<T,Rational<1,2>>>
    		( std::sqrt(x.getValue()) );
}

template<class M1, class M2, class L1, class L2, class T1, class T2>
constexpr bool same_dim(const Quantity<M1,L1,T1>& q1, const Quantity<M2,L2,T2>& q2){
	return R_is_equal<M1,M2>::value && R_is_equal<L1,L2>::value && R_is_equal<T1,T2>::value;
}

#endif // MY_UNITS_HPP_
