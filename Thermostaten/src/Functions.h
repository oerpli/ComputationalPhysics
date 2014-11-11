#pragma once

#include "Polymer.h" //redundant Thermostat
#include "Monomer.h" //redundant Polymer


#include<iostream>

using namespace std;

ostream& operator<<(ostream& os, const Monomer & mono);
ostream& operator<<(ostream& os, const Polymer & poly);


