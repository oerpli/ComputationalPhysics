#ifndef Functions_H
#define Functions_H

#include "Thermostate.h"
#include "Polymer.h" //redundant Thermostat
#include "Monomer.h" //redundant Polymer


#include<iostream>

using namespace std;

ostream& operator<<(ostream& os, const Monomer & mono) {
	mono.Print(os);
	return os;
}

ostream& operator<<(ostream& os, const Polymer & poly) {
	poly.Print(os);
	return os;
}

#endif
