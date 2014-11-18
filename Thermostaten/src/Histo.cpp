#include "Histo.h"
#include <vector>
#include <iostream>

using namespace std;

Histo::Histo() {output_reset();}

Histo::Histo(int in, double imin, double imax) {
	set(in,imin,imax);
	output_reset();
}	

void Histo::set(int in, double imin, double imax) {
	n = in;
	min = imin;
	max = imax;
	
	width = (max-min)/n;
	min_border = min + width;
	max_border = max - width;
	min_output = min + width * .5;
		
	hist.clear();
	hist.resize(n);
}

void Histo::set(int in, double imax) {set(in,-imax,imax);}

void Histo::add(double val) {
	count++;
	if ( val >= max || val < min ) return;
	if ( val < min_border ) hist[0]++;
	else if (val >= max_border ) hist[n-1]++;
	else hist[ (int) ( (val-min) / width ) ]++;
}

bool Histo::output(ostream& os) {
	if ( n_out >= n ) return false;
	os.precision(8);
	os << scientific;
	os << min_output + n_out * width << " ";
	os << hist[n_out] << " ";
	n_out++;
	return true;
}

bool Histo::output() {return output(cout);}

void Histo::output_reset() {n_out=0;}

void Histo::norm() {
	double scale{count * width};
	for (auto& s : hist) s /= scale;
}
