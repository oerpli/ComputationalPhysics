#include "Thermostat.h"
#include "Andersen.h"
#include "Lowe_Andersen.h"
#include "Gaussian.h"
#include "Nose_Hoover.h"

#include "consts.h"
using namespace consts;

#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdlib.h>     // atof
#include <cstring> //strcmp
using namespace std;


inline bool is_number(const std::string &str)
{
   return str.find_first_not_of(".eE-0123456789") == std::string::npos;
}

double set_param(double def, char *array[], int length, int pos) {
	if ( pos >= length ) return def;
	if ( is_number( array[pos] ) ) return stod( array[pos] );
	return def;
}


int main(int argc, char* argv[]) {
	double a_param[]{4, 20, 1E-15, 1E6};  //default für p,Temp,dtime,runs
	int			i_para{};
	
	for (i_para=0; i_para<min(4,argc-1); ++i_para) {
		if ( is_number(argv[i_para+1]) ) a_param[i_para]=stod(argv[i_para+1]);
		else break;
	}
	
	while ( i_para < argc - 1 && is_number( argv[i_para] ) ) ++i_para;
	
cout << argv[i_para] << endl;
	
	a_param[2] /= ref_time;
	Polymer poly{static_cast<unsigned> (a_param[0]), a_param[1]};
	


	if ( strcmp( argv[i_para] , "Andersen" ) == 0 ) {
		double nu{ set_param( .1, argv, argc, i_para+1 ) };
		Andersen thermostat{poly, a_param[2], nu};
	}
	else if ( strcmp( argv[i_para] , "Lowe_Andersen" ) == 0 ) {
		double nu{ set_param( .1, argv, argc, i_para+1 ) };
		Lowe_Andersen thermostat{poly, a_param[2], nu};
	}
	else if ( strcmp( argv[i_para] , "Gaussian" ) == 0 ) {
		Gaussian thermostat{poly, a_param[2]};
	}
	else if ( strcmp( argv[i_para] , "Nose_Hoover" ) == 0 ) {
		double q_def{poly.monomers.size()*poly.temp()*ref_time / 1E-14};
		double q{set_param (q_def, argv, argc, i_para+1) };
		Nose_Hoover thermostat{poly, a_param[2], q};
	}
  else { 
		cout << "Thermostat_None" << endl;
		return 1;
	}

	for (int i = 0; i < a_param[3]; i++) {
		if (!(i % (int)1E5)) {
			cout << "Ekin: " << poly.update_ekin() << endl;
			cout << "T: " << poly.calculate_temp() << endl;
		}
		thermostat.propagate();
	}
	
	return 0;
}
