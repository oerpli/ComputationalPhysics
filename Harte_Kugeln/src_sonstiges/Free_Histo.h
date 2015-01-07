#ifndef FREE_HISTO_H_
#define FREE_HISTO_H_

#include <map>
#include <iterator>
#include <cmath>
#include <iostream>

//Histogramm symmetrisch um 0
//frei in Klasseneinteilung
class Free_Histo {
private:
	std::map<double,unsigned> histo;
	std::map<double, unsigned>::iterator histo_iter;

	double width,scale;
	unsigned count;

	void add(double val, unsigned i);

public:
	Free_Histo();
	Free_Histo(double width);

	void operator ()(double val);

	bool output(std::ostream& os);

	void output_reset();

};
#endif //FREE_HISTO_H_
