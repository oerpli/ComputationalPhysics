#include "Functions.h"
#include "Polymer.h" //redundant Thermostat
#include "Monomer.h" //redundant Polymer

ostream& operator<<(ostream& os, const Monomer & mono) {
	print_m(mono, os);
	return os;
}

ostream& operator<<(ostream& os, const Polymer & poly) {
	poly.print(os);
	return os;
}


