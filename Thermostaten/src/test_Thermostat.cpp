#include "Thermostat.h"
#include "Andersen.h"
#include "Lowe_Andersen.h"
#include "Gaussian.h"
#include "Nose_Hoover.h"
#include "Thermostat_None.h"

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

ostream& operator<<(ostream& os, const Polymer & poly) {
	poly.print(os);
	return os;
}

/* ######################### */
int main(int argc, char* argv[]) {
	double a_param[]{4, 20, 1E-15, 1E6};  //default für p,Temp,dtime,runs
	int			i_para{1};
	
	for (i_para=1; i_para<min(5,argc); ++i_para) {
		if ( is_number(argv[i_para]) ) a_param[i_para-1]=stod(argv[i_para]);
		else break;
	}
	
	while ( i_para < argc - 1 && is_number( argv[i_para] ) ) ++i_para;
	
//cout << argv[i_para] << endl;
	
	a_param[2] /= ref_time;
	Polymer poly{static_cast<unsigned> (a_param[0]), a_param[1]};
	poly.initiate_monomers_random();
	
	// Initialisieren aller Thermostate
	double nu{ set_param( 1./a_param[2]/a_param[0], argv, argc, i_para+1 ) };
	Andersen andersen_therm{poly, a_param[2], nu};
	Lowe_Andersen lowe_andersen_therm{poly, a_param[2], nu};
	
	Gaussian gaussian_therm{poly, a_param[2]};

	double q_def{poly.monomers.size()*poly.temp()*ref_time / 1E-14};
	double q{set_param (q_def, argv, argc, i_para+1) };
	Nose_Hoover nose_hoover_therm{poly, a_param[2], q};
	
	Thermostat_None none_therm{poly, a_param[2]};
	
	// Auswählen des Thermostats
	Thermostat *thermostat{};
	if ( argc > 1 && i_para < argc ) {
		if ( strcmp( argv[i_para] , "Andersen" ) == 0 ) {
			thermostat = & andersen_therm;
		}
		else if ( strcmp( argv[i_para] , "Lowe_Andersen" ) == 0 ) {
			thermostat = & lowe_andersen_therm;
		}
		else if ( strcmp( argv[i_para] , "Gaussian" ) == 0 ) {
			thermostat = & gaussian_therm;
		}
		else if ( strcmp( argv[i_para] , "Nose_Hoover" ) == 0 ) {
			thermostat = & nose_hoover_therm;
		}
		else {
			thermostat = & none_therm;
		}
	}
  else {
		thermostat = & none_therm;
	}
	
	for (int i = 0; i < a_param[3]; i++) {
		if ( !( i % (int)(a_param[3]*1E-1*4) ) ) {
			cout << "Ekin: " << poly.update_ekin() << endl;
			cout << "T: " << poly.calculate_temp() << endl;
		}
		thermostat->propagate();
	}
	
	return 0;
}

