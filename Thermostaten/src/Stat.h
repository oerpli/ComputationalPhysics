#pragma once

#include <cmath>

class Stat {
private:
	double sum, sum2;
	int n;
public:
	double min, max;
	double sigma, mu;
	Stat();
	void add(double x);
	void calc();
	void reset();
};
