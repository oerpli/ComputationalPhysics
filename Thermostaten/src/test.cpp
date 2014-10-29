#include "Monomer.h"
#include "Functions.h"
#include "Thermostat_None.h"
#include "Nose_Hoover.h"

#include "consts.h"
using namespace consts;

#include<iostream>
#include<stdlib.h>

using namespace std;

int main() {

	cout << "Hello World" << endl;
	Polymer p_a(10, 15);
	cout << "T vor skalierung: " << p_a.ekin/p_a.monomers.size()/(0.5*ref_k) << endl;

	p_a.update_ekin();
	cout << "T nach skalierung: " << p_a.ekin/p_a.monomers.size()/(0.5*ref_k) << endl;

	Thermostat_None thermostat(p_a, 2E-3);

	for (int i = 0; i < 2E4; i++) {
		if (!(i % (int)5E3)) {
			cout << endl << p_a;
			cout << "Ekin: " << p_a.update_ekin() << endl;
		}
		thermostat.propagate();
	}

	cout << endl << p_a;
	cout << "Ekin: " << p_a.update_ekin() << endl;

	return 0;
}
