#include "Rand.h"

//Define static members
std::mt19937_64 Rand::generator(1);
std::normal_distribution<double> Rand::dis_normal;
std::uniform_real_distribution<double> Rand::dis_uniform;
std::uniform_int_distribution<int> Rand::dis_intuniform;
std::chi_squared_distribution<double> Rand::dis_chisquared;

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

double Rand::real_chisquared(unsigned n){
	dis_chisquared.param((std::chi_squared_distribution<double>::param_type)n);
	return dis_chisquared(generator);
}
