#ifndef TEMPLATE_RATIONAL_HPP_
#define TEMPLATE_RATIONAL_HPP_

#include<iostream>


template<int a>
struct equal_zero{
	static const bool value = false;
};

template<>
struct equal_zero<0>{
	static const bool value = true;
};


template<int a>
struct abs_t{
	static const unsigned value = ( a < 0 ) ? -a : a;
};


template<int a, int b>
struct calc_gcd{
	static const int value = calc_gcd<b, a%b>::value;
};

template<int a>
struct calc_gcd<a,0> {
	static const int value = abs_t<a>::value;
};

// container for numerator and denominator
template<int num, unsigned den>
struct Rat {
	static const int v_num = num;
	static const unsigned v_den = den;
};

//catch division 0
template<int num>
struct Rat<num, 0>;


template<int num, unsigned den>
struct Rational_min {
	static const int gcd = calc_gcd<num,den>::value;
	using value = Rat<num / gcd, den / gcd>;
};

// zero is representet by 0/1
template<int den>
struct Rational_min<0, den> {
	using value = Rat<0,1>;
};

// defining Rational
template<int num, unsigned den>
using Rational = typename Rational_min<num,den>::value;


// Raw addition of rational numbers
template<int num1, unsigned den1, int num2, unsigned den2>
struct R_add_meta{
	static const unsigned den = den1 * den2;
	using value = typename R_add_meta<num1 * den2, den, num2 * den1, den>::value;
};

// addition for same denominator
template<int num1, int num2, unsigned den>
struct R_add_meta<num1, den, num2, den>{
	using value = Rational<num1+num2, den>;
};

template<class R1, class R2>
using R_add = typename R_add_meta<R1::v_num, R1::v_den, R2::v_num, R2::v_den>::value;


template<class R>
using R_neg = Rat<-R::v_num, R::v_den>;

template<class R1, class R2>
using R_sub = R_add<R1, R_neg<R2>>;


template<class R1, class R2>
using R_mul = Rational<R1::v_num * R2::v_num, R1::v_den * R2::v_den>;


template<int num, unsigned den>
struct R_inv_meta{
	using value = Rat< (num < 0) ? -den : den, abs_t<num>::value>;
};

template<unsigned den>
struct R_inv_meta<0,den>{
	using value = Rat<0,1>;
};

template<class R>
using R_inv = typename R_inv_meta<R::v_num, R::v_den>::value;

template<class R1, class R2>
using R_div = R_mul<R1, R_inv<R2>>;


template<int num, unsigned den>
struct R_print_raw{
	static constexpr std::ostream& print(std::ostream& os = std::cout) {
		return os << num << '/' << den;
	}
};

template<int num>
struct R_print_raw<num,1>{
	static constexpr std::ostream& print(std::ostream& os) {
		return os << num;
	}
};

template<class R>
struct R_print{
	static constexpr std::ostream& print(std::ostream& os = std::cout) {
		return R_print_raw<R::v_num, R::v_den>::print(os);
	}
};

#endif //TEMPLATE_RATIONAL_HPP_
