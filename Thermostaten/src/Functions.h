#pragma once

#include "Polymer.h" //redundant Thermostat
#include "Monomer.h" //redundant Polymer

#include "Stat.h"
#include "Histo.h"
#include <vector>
#include <string>
#include <sstream>

#include<iostream>

using namespace std;

ostream& operator<<(ostream& os, const Monomer & mono);
ostream& operator<<(ostream& os, const Polymer & poly);

bool is_number(const std::string &str);
double set_param(double def, char *array[], int length, int pos);

void assign(istringstream &iss, const string &str);
ostream& operator<<(ostream& os, const Stat& stat);
bool histoLine(vector<Histo> &v_h, ostream &os);
bool histoLine(vector<Histo> &v_h);
ostream& operator << (ostream& os, vector<Histo> &v_h);
