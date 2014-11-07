#include<iostream>
#include<fstream>
#include<stdlib.h>
#include "Monomer.h"
#include "Functions.h"
#include "Thermostat_None.h"
#include "Nose_Hoover.h"
#include "consts.h"

using namespace consts;
using namespace std;

int main() {
        ofstream MyFile; 
	cout << "Hello World" << endl;
	Polymer p_a(10, 20);
	p_a.initiate_monomers_random();
	cout << "T vor skalierung: " << p_a.ekin / p_a.monomers.size() / (0.5*ref_k) << endl;

	p_a.update_ekin();
	cout << "T nach skalierung: " << p_a.calculate_temp() << endl;
	double step = 1E-15 / ref_time; 
	double q = p_a.monomers.size()*p_a.temp()*ref_time / 1E-13; 
	cout << "q = " << q << endl; 
	//Thermostat_None thermostat(p_a, 1E-15 / ref_time);
	Nose_Hoover thermostat(p_a, q, step);  
	MyFile.open("Nose_Hoover.dat", ios::out | ios::trunc); 

	for (int i = 0; i < 1E6; i++) {
		if (!(i % (int)1E2)) {
		  cout << endl << i << endl; 
		  //cout << endl << p_a;
			cout << "Ekin: " << p_a.update_ekin() << endl;
			cout << "T: " << p_a.calculate_temp() << endl;
			MyFile << i*step << " " << p_a.calculate_temp() << endl; 
		}
		thermostat.propagate();
	}
	MyFile.close();
	cout << endl << p_a;
	cout << "Ekin: " << p_a.update_ekin() << endl;
	cout << "T: " << p_a.calculate_temp() << endl;

	return 0;
}
