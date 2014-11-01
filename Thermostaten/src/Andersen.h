#ifndef ANDERSEN_H
#define ANDERSEN_H

#include "Polymer.h"
#include "consts.h"

#include<cmath>
#include<random>


class Andersen {
private:
	Polymer& m_poly;
	double m_dtime, m_dtime2;
        double m_nu, m_nu_dt, m_sigma;
        
        std::default_random_engine generator;
        std::uniform_real_distribution<double>  uniform_real;
        std::normal_distribution<double>        gauss_real;
        
public:
        double time;
        
	Andersen(Polymer &poly, double dtime, double nu );

        double  time_step();
        double  time_step(double dtime);
        
        double  update_sigma();
	void    propagate();
};
#endif 

