#include <iostream>
#include <random>

#include "Free_Histo.h"

using namespace std;

int main() {
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0,2.0);
  double value { };

  Free_Histo histo1{1},histo05{0.5},histo01{0.1};

  unsigned runs{ (unsigned) 1E3 };
  for (unsigned i=0; i<runs; ++i) {
	value = distribution(generator);
	histo1( value );
	histo05( value );
	histo01( value );
  }
  bool out {};
  do {
	  out = histo1.output(cout);
	  out = histo05.output(cout);
	  out = histo01.output(cout) || out;
	  cout << '\n';
  } while(out);
}
