#include "Monomer.h"
#include "Functions.h"
#include "Thermostat_None.h"
#include "Nose_Hoover.h"

#include<iostream>
#include<stdlib.h>

using namespace std;

int main() {

	cout << "Hello World" << endl;

	Polymer p_a(64);
	cout << "ekin vor skalierung: " << p_a.ekin << endl; 

	p_a.update_ekin(); 
	cout << "ekin nach skalierung: " << p_a.ekin << endl; 

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
