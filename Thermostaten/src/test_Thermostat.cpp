#include "Thermostat.h"
#include "Nose_Hoover_Chain.h"
#include "Andersen.h"
#include "Lowe_Andersen.h"
#include "Gaussian.h"
#include "Nose_Hoover.h"
#include "Thermostat_None.h"
#include "Berendsen.h"
#include "Bussi.h"

#include "Functions.h"
#include "consts.h"
using namespace consts;

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;


/* ######################### */
int main(int argc, char* argv[]) {
	//default für  p,Temp,dtime,runs,warmlauf,ausgabe   :jedes xte wird ausgegeben
	double a_para[]{4, 20, 1E-15, 1E6, 1E3, 1};
	int			i_para{ 1 };
	string s_para{}, s_therm{};
	string	s_temp{}, s_pos_vel{};
	ofstream dat_temp{}, dat_pos_vel{};
	Thermostat *thermostat{};

	// Bestimmen der Parameter zur Initialisierung von Poly und Thermostat
	for (i_para = 1; i_para < min(7, argc); ++i_para) {
		if (is_number(argv[i_para])) a_para[i_para - 1] = stod(argv[i_para]);
		else break;
	}
	a_para[2] /= ref_time;

	while (i_para < argc - 1 && is_number(argv[i_para])) ++i_para;
	int i_thermos = i_para;

	while (++i_para < argc - 1 && is_number(argv[i_para])) ++i_para;
	int i_poly_init = min(argc - 1, i_para);

	Polymer poly{ static_cast<unsigned> (a_para[0]), a_para[1] };
	if (strcmp(argv[i_poly_init], "one") == 0)
		poly.initiate_monomers_one();
	else
		poly.initiate_monomers_random();

	// Auswählen des Thermostats
	if (argc > 1 && i_thermos < argc) {
		if (strcmp(argv[i_thermos], "Andersen") == 0) {
			double nu{ set_param(1. / a_para[2] / a_para[0], argv, argc, i_thermos + 1) };
			thermostat = new Andersen{ poly, a_para[2], nu };
			s_therm = "Andersen";
		}
		else if (strcmp(argv[i_thermos], "Lowe_Andersen") == 0) {
			double nu{ set_param(1. / a_para[2] / a_para[0], argv, argc, i_thermos + 1) };
			thermostat = new Lowe_Andersen{ poly, a_para[2], nu };
			s_therm = "Lowe_Andersen";
		}
		else if (strcmp(argv[i_thermos], "Gaussian") == 0) {
			thermostat = new Gaussian{ poly, a_para[2] };
			s_therm = "Gaussian";
		}
		else if (strcmp(argv[i_thermos], "Nose_Hoover") == 0) {
			double q_def{ poly.monomers.size()*poly.target_temperature()*ref_time / 1E-12 };
			double q{ set_param(q_def, argv, argc, i_thermos + 1) };
			thermostat = new Nose_Hoover{ poly, a_para[2], q };
			s_therm = "Nose_Hoover";
		}
		else if (strcmp(argv[i_thermos], "Nose_Hoover_Chain") == 0) {
		  double q_def{ poly.monomer_mass*poly.target_temperature()/poly.feder_konst() };
			double q{ set_param(q_def * poly.monomers.size() , argv, argc, i_thermos + 1) };
			double q2{ set_param( q_def , argv, argc, i_thermos + 2 ) };
			thermostat = new Nose_Hoover_Chain{ poly, a_para[2], q, q2 };
			s_therm = "Nose_Hoover_Chain";
		}
		else if (strcmp(argv[i_thermos], "Berendsen") == 0) {
			double couplingtime = 10 * a_para[2];
			thermostat = new Berendsen{ poly, a_para[2], couplingtime };
			s_therm = "Berendsen";
		}
		else if (strcmp(argv[i_thermos], "Bussi") == 0) {
			double couplingtime = 10 * a_para[2];
			thermostat = new Bussi{ poly, a_para[2], couplingtime };
			s_therm = "Bussi";
		}
		else {
			thermostat = new Thermostat_None{ poly, a_para[2] };
			s_therm = "None";
		}
	}
	else {
		thermostat = new Thermostat_None{ poly, a_para[2] };
		s_therm = "None";
	}
	cout << "Thermostat:\t" << s_therm << endl;
	s_para = "_p"; s_para += to_string((int)a_para[0]);
	s_para += "_T"; s_para += to_string((int)a_para[1]);

	s_temp = s_therm + "_temp" + s_para + ".dat";
	dat_temp.open(s_temp, ios::out | ios::trunc);

	s_pos_vel = s_therm + "_pos_vel" + s_para + ".dat";
	dat_pos_vel.open(s_pos_vel, ios::out | ios::trunc);

	// Simulation
	for (int i = 0; i < a_para[4]; ++i) thermostat->propagate();
	cout << "Warmlauf abgeschlossen" << endl;

	int index_print{ (int)(a_para[3] * 4E-1) };
	int index_to_file{ (int)a_para[5] };
	for (int i = 0; i < a_para[3]; i++) {
		if (!(i % index_to_file)) {
			dat_temp << i*a_para[2];
			dat_temp << " " << poly.calculate_temp();
			dat_temp << " " << poly.update_epot()  << endl;
			dat_pos_vel << poly;
		}

		if (!(i % index_print)) {
			cout << i*a_para[2] << endl;
			cout << "Ekin: " << poly.update_ekin() << endl;
			cout << "T: " << poly.calculate_temp() << endl;
		}
		thermostat->propagate();
	}
	delete thermostat;

	cout << "<< Die Datei '" << s_temp << "' wurde erstellt." << endl;
	cout << "<< Die Datei '" << s_pos_vel << "' wurde erstellt." << endl;

	dat_temp.close();
	dat_pos_vel.close();
	return 0;
}

