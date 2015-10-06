#include "Stat.h"
#include <cmath>
#include <float.h>

using namespace std;

Stat::Stat() {
	reset();
}
void Stat::add(double x) {
	++n;
	sum += x;
	sum2 += pow(x, 2);

	if (x < min) min = x;
	if (x > max) max = x;
}

void Stat::calc() {
	if (n < 2) return;
	mu = sum / n;
	sigma = sqrt((sum2 - n * pow(mu, 2)) / (n - 1));
}

void Stat::reset() {
	sum = sum2 = sigma = mu = 0;
	n = 0;
	min = DBL_MAX; //instead of +-infinity to prevent overflow warnin.g
	max = DBL_MIN;
}