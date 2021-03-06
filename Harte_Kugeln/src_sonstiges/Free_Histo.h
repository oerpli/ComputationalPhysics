#ifndef FREE_HISTO_H_
#define FREE_HISTO_H_

#include <map>
#include <iterator>
#include <cmath>
#include <iostream>

//Histogramm symmetrisch um 0
//frei in Klasseneinteilung
class Free_Histo {
protected:
	std::map<double,unsigned> histo;
	std::map<double, unsigned>::iterator histo_iter;

	double width, center_left, offset, scale;
	unsigned count;

	virtual void add(double val, unsigned i);
public:
	Free_Histo();
	Free_Histo(double width, double offset = 0.0, bool center = true);
	Free_Histo(double width, bool center, double offset = 0.0);

	void operator ()(double val);

	virtual bool output(std::ostream& os);

	void output_reset();

	unsigned get_count() const {return count;}
};
#endif //FREE_HISTO_H_
