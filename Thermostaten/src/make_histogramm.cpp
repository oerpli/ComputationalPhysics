#include "Stat.h"
#include "Histo.h"
#include "Functions.h"

#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <stdlib.h>

#include <cmath>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	string filename{argv[1]};
	ifstream input(filename);
	ofstream output;
	istringstream iss;
	string line{};
	
	string s_header;
	streampos pos_header;
	
	int columns{}, histoN {500};
	double val;
	vector <Stat> v_stat;
	vector <Histo> v_histo;
	
	output.open(filename.insert(filename.find(".dat"),"_histo"), ios::out | ios::trunc);
	
	if (argc > 2) histoN = stod(argv[2]);
	
	pos_header=input.tellg();
	for (getline(input,line); !line.compare(0, 1, "#"); getline(input,line)) {
		s_header += line;
		s_header += '\n';
	pos_header=input.tellg();
	}
	
	assign(iss,line);
	for (columns=0; ! iss.eof() ; ++columns) iss >> val;
	v_stat.resize(columns);
	v_histo.resize(columns);
	
	input.clear();
	input.seekg(pos_header);
	for ( ; getline(input,line); ) {
		assign(iss,line);
		for ( int i=0 ; ! iss.eof() ; ++i) {
			iss >> val;
			v_stat[i].add(val);
		} 
	}
	
	for (auto& stat : v_stat)
		stat.calc();
	
	double borderH {};
	for (int i=0; i < columns; i++) {
		borderH=max( abs(v_stat[i].min) , abs(v_stat[i].max) );
		v_histo[i].set(histoN,-borderH,borderH);
	}
	
	input.clear();
	input.seekg(pos_header);
	for ( ; getline(input,line); ) {
		assign(iss,line);
		for ( int i=0 ; ! iss.eof() ; ++i) {
			iss >> val;
			v_histo[i].add(val);
		} 
	}	
	input.close();

	for (auto& h : v_histo) h.norm();
	
	output << s_header;
	output << "# " << scientific;
	for (auto& stat : v_stat) output << stat.mu << " " << stat.sigma << " ";
	output << endl;
	output << v_histo;
	
	cout << "<< Die Datei '" << filename << "' wurde erstellt." << endl;
	output.close();
return 0;
}
