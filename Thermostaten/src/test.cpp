#include "Monomer.h"
#include "Functions.h"
#include "Thermostat_None.h"
#include "Nose_Hoover.h"

#include<iostream>
#include<stdlib.h>

using namespace std;

int main() {

	cout << "Hello World" << endl;

	Polymer p_a(10);
	cout << "T vor skalierung: " << p_a.ekin*2.0/(p_a.monomers.size() -1) << endl; 

	p_a.update_ekin(); 
	cout << "T nach skalierung: " << p_a.ekin*2.0/(p_a.monomers.size() -1) << endl; 

	Thermostat_None thermostat(p_a, 0.001); 
	//Nose_Hoover thermostat(p_a, 1.0, 0.1);

	cout << p_a << endl;
	//cout << "calculation no thermostat" << endl;

	//cout << p_a << endl;
	//cout << "calculation N-H" << endl;
	//thermostat.Propagate(1.);
	//cout << p_a << endl;

	return 0;
}
