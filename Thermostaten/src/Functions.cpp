#include "Functions.h"
#include "Polymer.h" //redundant Thermostat
#include "Monomer.h" //redundant Polymer

#include "Stat.h"
#include "Histo.h"
#include <vector>
#include <string>
#include <sstream>

#include<iostream>

using namespace std;

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
	if (pos >= length) return def;
	if (is_number(array[pos])) return stod(array[pos]);
	return def;
}

void assign(istringstream &iss, const string &str) {
	iss.clear();
	iss.str(str);
}

ostream& operator<<(ostream& os, const Stat& stat) {
	os << stat.mu << " " << stat.sigma << " ";
	os << stat.min << " " << stat.max;
return os;
}

bool histoLine(vector<Histo> &v_h, ostream &os) {
	bool ret=false;
	for (auto& h : v_h ) ret = ret | h.output(os);
	return ret;
}
bool histoLine(vector<Histo> &v_h) {return histoLine(v_h,cout);}

ostream& operator << (ostream& os , vector<Histo> &v_h) {
	while ( histoLine(v_h,os) ) os << endl; 
	for (auto& h : v_h) h.output_reset();
return os;
}
