#ifndef HISTO_H
#define HISTO_H

#include <vector>
#include <ostream>

class Histo {
private:
	std::vector<double> hist;
	double min, max, width;
	double min_border, max_border, min_output;
	int n, n_out, count;
	
public:
	Histo();
	Histo(int in, double imin, double imax);
	void set(int in, double imin, double imax);
	void add(double val);
	bool output(std::ostream& os);
	bool output();
	void output_reset();
	void norm();
};
#endif
