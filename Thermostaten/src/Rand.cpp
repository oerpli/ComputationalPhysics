#include "Rand.h"
using namespace std;

//Define static members
mt19937_64 Rand::generator(1);
normal_distribution<double> Rand::dis_normal;
uniform_real_distribution<double> Rand::dis_uniform;
uniform_int_distribution<int> Rand::dis_intuniform;
chi_squared_distribution<double> Rand::dis_chisquared;

double Rand::real_normal(){
	return Rand::dis_normal(Rand::generator);
}
double Rand::real_normal(double mean, double std){
	return (Rand::real_normal()*std) + mean;
}

double Rand::real_uniform(){
	return Rand::dis_uniform(Rand::generator);
}
double Rand::real_uniform(double max){
	return Rand::real_uniform()*max;
}
double Rand::real_uniform(double min, double max){
	return Rand::real_uniform()*(max - min) + min;
}

void Rand::real_chisquared_set(int n) {
	if ( n == dis_chisquared.n() ) return;
	chi_squared_distribution<double> buf_chi2(n);
	dis_chisquared.param( buf_chi2.param() );
}

double Rand::real_chisquared(int n){
	real_chisquared_set(n);
	return dis_chisquared(generator);
}
