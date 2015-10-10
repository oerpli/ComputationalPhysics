#include "Rand.h"
using namespace std;

//Define static members
mt19937_64 Rand::generator(1);
normal_distribution<double> Rand::dis_normal;
uniform_real_distribution<double> Rand::dis_uniform;
uniform_int_distribution<int> Rand::dis_intuniform;
chi_squared_distribution<double> Rand::dis_chisquared;
gamma_distribution<double> Rand::dis_gamma;

double Rand::real_normal() {
	return Rand::dis_normal(Rand::generator);
}
double Rand::real_normal(double mean, double std) {
	return (Rand::real_normal()*std) + mean;
}

double Rand::real_uniform() {
	return Rand::dis_uniform(Rand::generator);
}
double Rand::real_uniform(double max) {
	return Rand::real_uniform()*max;
}
double Rand::real_uniform(double min, double max) {
	return Rand::real_uniform()*(max - min) + min;
}

double Rand::real_chisquared(unsigned n) {
	dis_chisquared.param((chi_squared_distribution<double>::param_type)n);
	return dis_chisquared(generator);
}

double Rand::real_gamma(double k, double theta) {
	static double K = 0.0, Theta = 0.0;
	if (K != k || Theta != theta) {
		K = k;
		Theta = theta;
		dis_gamma = gamma_distribution<double>(K, Theta);
		//beware: 2 parametrizations usual: (k,theta) and (alpha,beta) = (k,1/theta)
		//C++ uses alpha and beta but (alpha,beta) = (k,theta)
	}
	return dis_gamma(generator);
}