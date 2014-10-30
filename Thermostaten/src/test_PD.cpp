#include "Polymer.h"
#include "Functions.h"

#include "consts.h"
using namespace consts;

#include<iostream>
#include<stdlib.h>

#include<random>

#include "Andersen.h"
#include "Thermostat_None.h"

using namespace std;

int main() {
  
  Polymer p_a(60, 1);
  Andersen thermostat(p_a,1E-15/ref_time,20);
//	Thermostat_None thermostat(p_a, 1E-15/ref_time);
  
  for (int i = 0; i < 1E6; i++) {
		if (!(i % (int)5E6)) {
			cout << endl << p_a;
			cout << "Ekin: " << p_a.update_ekin() << endl;
      cout << "T: " << p_a.ekin/p_a.monomers.size()/(0.5*ref_k) << endl;
      cout << "T: " << p_a.calculate_temp() << endl;
		}
		thermostat.propagate();
	}

			cout << endl << p_a;
			cout << "Ekin: " << p_a.update_ekin() << endl;
      cout << "T: " << p_a.ekin/p_a.monomers.size()/(0.5*ref_k) << endl;
      cout << "T: " << p_a.calculate_temp() << endl;
  
cout << p_a.monomer_mass << endl;
return 0;
}
