#include "Rand.h"
using namespace std;

//Define static members
mt19937_64 Rand::generator = mt19937_64(chrono::system_clock::now().time_since_epoch().count());
normal_distribution<double> Rand::dis_normal;
uniform_real_distribution<double> Rand::dis_uniform;
uniform_int_distribution<int> Rand::dis_intuniform;

double Rand::real_normal(){
	return Rand::dis_normal(Rand::generator);
}
double Rand::real_normal(double mean, double std){
	double rnd = Rand::dis_normal(Rand::generator);
	return (rnd*std) + mean;
}

double Rand::real_uniform(){
	return Rand::dis_uniform(Rand::generator);
}
double Rand::real_uniform(double max){
	return Rand::dis_uniform(Rand::generator)*max;
}
double Rand::real_uniform(double min, double max){
	double rnd = Rand::dis_uniform(Rand::generator);
	return (rnd)*(max - min) + min;
}
