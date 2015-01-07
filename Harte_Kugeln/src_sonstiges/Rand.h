#pragma once

#include <random>
#include <chrono>
//schreibt hier schonmal rein wenn ihr irgendwelche spezielle sachen wollt. 

using namespace std;

class Rand{
private:
	static mt19937_64 generator;
	static normal_distribution<double> dis_normal;
	static uniform_real_distribution<double> dis_uniform;
	static uniform_int_distribution<int> dis_intuniform;
	static chi_squared_distribution<double> dis_chisquared;
public:
	static void init();
	static double real_normal(double, double);
	static double real_normal();
	static double real_uniform();
	static double real_uniform(double);
	static double real_uniform(double, double);
	static double real_chisquared(unsigned n);
};
