#ifndef LOWE_ANDERSEN_H
#define LOWE_ANDERSEN_H

#include "Polymer.h"
#include "consts.h"

#include<cmath>
#include<random>


class Lowe_Andersen {
private:
	Polymer& poly;
	double dtime, dtime2;
        double nu, nu_dt, sigma;
        
        std::default_random_engine generator;
        std::uniform_real_distribution<double>  uniform_real;
        std::normal_distribution<double>        gauss_real;
        
public:
        double time;
        
	Lowe_Andersen(Polymer &poly, double dtime, double nu );

        double  time_step();
        double  time_step(double dt);
        
        double  update_sigma();
	void    propagate();
};
#endif 

