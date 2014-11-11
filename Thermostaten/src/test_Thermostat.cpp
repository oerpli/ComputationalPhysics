#include "Thermostat.h"
#include "Andersen.h"
#include "Lowe_Andersen.h"
#include "Gaussian.h"
#include "Nose_Hoover.h"
#include "Thermostat_None.h"

#include "Functions.h"
#include "consts.h"
using namespace consts;

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;


/* ######################### */
int main(int argc, char* argv[]) {
	//default für  p,Temp,dtime,runs,warmlauf
	double a_para[]{4, 20, 1E-15, 1E6, 1E3};
	int			i_para{ 1 };
	string s_para{}, s_therm{};
	string	s_temp{}, s_pos_vel{};
	ofstream dat_temp{}, dat_pos_vel{};
	Thermostat *thermostat{};

	// Bestimmen der Parameter zur Initialisierung von Poly und Thermostat
	for (i_para = 1; i_para < min(6, argc); ++i_para) {
		if (is_number(argv[i_para])) a_para[i_para - 1] = stod(argv[i_para]);
		else break;
	}

	while (i_para < argc - 1 && is_number(argv[i_para])) ++i_para;

	a_para[2] /= ref_time;
	Polymer poly{ static_cast<unsigned> (a_para[0]), a_para[1] };
	poly.initiate_monomers_random();

	s_para = "_p"; s_para += to_string((int)a_para[0]);
	s_para += "_T"; s_para += to_string((int)a_para[1]);

	// Initialisieren aller Thermostate
	double nu{ set_param(1. / a_para[2] / a_para[0], argv, argc, i_para + 1) };
	Andersen andersen_therm{ poly, a_para[2], nu };
	Lowe_Andersen lowe_andersen_therm{ poly, a_para[2], nu };

	Gaussian gaussian_therm{ poly, a_para[2] };

	double q_def{ poly.monomers.size()*poly.target_temperature()*ref_time / 1E-14 };
	double q{ set_param(q_def, argv, argc, i_para + 1) };
	Nose_Hoover nose_hoover_therm{ poly, a_para[2], q };

	Thermostat_None none_therm{ poly, a_para[2] };

	// Auswählen des Thermostats
	if (argc > 1 && i_para < argc) {
		if (strcmp(argv[i_para], "Andersen") == 0) {
			thermostat = &andersen_therm;
			s_therm = "Andersen";
		}
		else if (strcmp(argv[i_para], "Lowe_Andersen") == 0) {
			thermostat = &lowe_andersen_therm;
			s_therm = "Lowe_Andersen";
		}
		else if (strcmp(argv[i_para], "Gaussian") == 0) {
			thermostat = &gaussian_therm;
			s_therm = "Gaussian";
		}
		else if (strcmp(argv[i_para], "Nose_Hoover") == 0) {
			thermostat = &nose_hoover_therm;
			s_therm = "Nose_Hoover";
		}
		else {
			thermostat = &none_therm;
			s_therm = "None";
		}
	}
	else {
		thermostat = &none_therm;
		s_therm = "None";
	}

	s_temp = s_therm + "_temp" + s_para + ".dat";
	dat_temp.open(s_temp, ios::out | ios::trunc);

	s_pos_vel = s_therm + "_pos_vel" + s_para + ".dat";
	dat_pos_vel.open(s_pos_vel, ios::out | ios::trunc);

	// Simulation
	for (int i = 0; i < a_para[4]; ++i) thermostat->propagate();
	cout << "Warmlauf abgeschlossen" << endl;

	int index_print{ (int)(a_para[3] * 4E-1) };
	for (int i = 0; i < a_para[3]; i++) {
		dat_temp << i*a_para[2] << " " << poly.calculate_temp() << endl;
		dat_pos_vel << poly;

		if (!(i % index_print)) {
			cout << i*a_para[2] << endl;
			cout << "Ekin: " << poly.update_ekin() << endl;
			cout << "T: " << poly.calculate_temp() << endl;
		}

		thermostat->propagate();
	}

	cout << "<< Die Datei '" << s_temp << "' wurde erstellt." << endl;
	cout << "<< Die Datei '" << s_pos_vel << "' wurde erstellt." << endl;

	dat_temp.close();
	dat_pos_vel.close();
	return 0;
}

