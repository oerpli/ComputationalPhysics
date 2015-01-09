#pragma once

#include <random>
#include <chrono>
//schreibt hier schonmal rein wenn ihr irgendwelche spezielle sachen wollt. 

class Rand{
private:
	static std::mt19937_64 generator;
	static std::normal_distribution<double> dis_normal;
	static std::uniform_real_distribution<double> dis_uniform;
	static std::uniform_int_distribution<int> dis_intuniform;
	static std::chi_squared_distribution<double> dis_chisquared;
public:
	static void init();
	static double real_normal(double, double);
	static double real_normal();
	static double real_uniform();
	static double real_uniform(double);
	static double real_uniform(double, double);
	static double real_chisquared(unsigned n);
};
