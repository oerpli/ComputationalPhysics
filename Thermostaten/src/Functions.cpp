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

bool is_number(const std::string &str)
{
   return str.find_first_not_of(".eE-0123456789") == std::string::npos;
}

double set_param(double def, char *array[], int length, int pos) {
	if ( pos >= length ) return def;
	if ( is_number( array[pos] ) ) return stod( array[pos] );
	return def;
}
