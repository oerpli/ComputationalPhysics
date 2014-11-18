#include<stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>

#include <cmath>
#include <algorithm>

using namespace std;


class Stat {
private:
	double sum, sum2;
	int n;
public:
	double min, max;
	double sigma, mu;
	Stat() {reset();}
	void add(double x) {
		++n;
		sum += x;
		sum2 += pow(x,2);
		
		if ( x < min ) min = x;
		if ( x > max ) max = x;
	}
	void calc() {
		if ( n < 2 ) return;
		mu = sum / n;
		sigma = sqrt( (sum2 - n * pow(mu,2) ) / (n-1) );
	}
	void reset() {
		sum = sum2 = sigma = mu = 0;
		n=0;
		min = INFINITY;
		max = -INFINITY;
	}
};

class Histo {
private:
	vector<double> hist;
	double min, max, width;
	double min_border, max_border, min_output;
	int n, n_out;
	
public:
	Histo() {output_reset();}
	Histo(int in, double imin, double imax) {
		set(in,imin,imax);
		output_reset();
	}	
	void set(int in, double imin, double imax) {
		n = in;
		min = imin;
		max = imax;
		
		width = (max-min)/n;
		min_border = min + width;
		max_border = max - width;
		min_output = min + width * .5;
			
		hist.clear();
		hist.resize(n);
	}
	void add(double val) {
		if ( val < min_border ) hist[0]++;
		else if (val >= max_border ) hist[n-1]++;
		else hist[ (int) ( (val-min) / width ) ]++;
	}
	bool output(ostream& os=cout) {
		if ( n_out >= n ) return false;
		os.precision(8);
		os << scientific;
		os << min_output + n_out * width << " ";
		os << hist[n_out] << " ";
		n_out++;
		return true;
	}
	void output_reset() {n_out=0;}
	void norm() {
		double scale{};
		for (auto& s : hist) scale += s;
		scale *= width;
		
		for (auto& s : hist) s /= scale;
	}
};

void assign(istringstream &iss, const string &str) {
	iss.clear();
	iss.str(str);
}

ostream& operator<<(ostream& os, const Stat& stat) {
	os << stat.mu << " " << stat.sigma << " ";
	os << stat.min << " " << stat.max;
return os;
}

bool histoLine(vector<Histo> &v_h, ostream &os=cout) {
	bool ret=false;
	for (auto& h : v_h ) ret = ret | h.output(os);
	return ret;
}

ostream& operator << (ostream& os , vector<Histo> &v_h) {
	while ( histoLine(v_h,os) ) os << endl; 
	for (auto& h : v_h) h.output_reset();
return os;
}

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
	output << v_histo;
	
	cout << "<< Die Datei '" << filename << "' wurde erstellt." << endl;
	output.close();
return 0;
}
