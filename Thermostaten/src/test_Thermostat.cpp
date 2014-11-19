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
	double para_p, para_temp, para_dtime, para_runs, para_warm, para_aus;
	int			i_para{ 1 };
	string s_para{};
	string	s_temp{}, s_pos_vel{};
	ofstream dat_temp{}, dat_pos_vel{};
	Thermostat *thermostat{};

	// Bestimmen der Parameter zur Initialisierung von Poly und Thermostat
	for (i_para = 1; i_para < min(7, argc); ++i_para) {
		if (is_number(argv[i_para])) a_para[i_para - 1] = stod(argv[i_para]);
		else break;
	}
	para_p = a_para[0];
	para_temp = a_para[1];
	para_dtime = a_para[2] / ref_time;
	para_runs = a_para[3];
	para_warm = a_para[4];
	para_aus = a_para[5];

	while (i_para < argc - 1 && is_number(argv[i_para])) ++i_para;
	int i_thermos = i_para;

	while (++i_para < argc - 1 && is_number(argv[i_para])) ++i_para;
	int i_poly_init = min(argc - 1, i_para);

	Polymer poly{ static_cast<unsigned> (para_p), para_temp };
	if (strcmp(argv[i_poly_init], "one") == 0)
		poly.initiate_monomers_one();
	else
		poly.initiate_monomers_random();

	// Auswählen des Thermostats
	if (argc > 1 && i_thermos < argc) {
		if (strcmp(argv[i_thermos], "Andersen") == 0) {
			double nu{ set_param(1. / para_dtime / para_p, argv, argc, i_thermos + 1) };
			thermostat = new Andersen{ poly, para_dtime, nu };
		}
		else if (strcmp(argv[i_thermos], "Lowe_Andersen") == 0) {
			double nu{ set_param(1. / para_dtime / para_p, argv, argc, i_thermos + 1) };
			thermostat = new Lowe_Andersen{ poly, para_dtime, nu };
		}
		else if (strcmp(argv[i_thermos], "Gaussian") == 0) {
			thermostat = new Gaussian{ poly, para_dtime };
		}
		else if (strcmp(argv[i_thermos], "Nose_Hoover") == 0) {
			double q_def{ poly.monomers.size()*poly.target_temperature()*ref_time / 1E-12 };
			double q{ set_param(q_def, argv, argc, i_thermos + 1) };
			thermostat = new Nose_Hoover{ poly, para_dtime, q };
		}
		else if (strcmp(argv[i_thermos], "Nose_Hoover_Chain") == 0) {
			double q_def{ poly.monomer_mass*poly.target_temperature() / poly.feder_konst() };
			double q{ set_param(q_def * poly.monomers.size(), argv, argc, i_thermos + 1) };
			double q2{ set_param(q_def, argv, argc, i_thermos + 2) };
			thermostat = new Nose_Hoover_Chain{ poly, para_dtime, q, q2 };
		}
		else if (strcmp(argv[i_thermos], "Berendsen") == 0) {
			double couplingtime = 10 * para_dtime;
			thermostat = new Berendsen{ poly, para_dtime, couplingtime };
		}
		else if (strcmp(argv[i_thermos], "Bussi") == 0) {
			double couplingtime = 10 * para_dtime;
			thermostat = new Bussi{ poly, para_dtime, couplingtime };
		}
		else {
			thermostat = new Thermostat_None{ poly, para_dtime };
		}
	}
	else {
		thermostat = new Thermostat_None{ poly, para_dtime };
	}
	cout << "Thermostat:\t" << thermostat->name() << endl;

	s_para = "_p"; s_para += to_string((int)para_p);
	s_para += "_T"; s_para += to_string((int)para_temp);

	s_temp = thermostat->name() + "_temp" + s_para + ".dat";
	dat_temp.open(s_temp, ios::out | ios::trunc);

	s_pos_vel = thermostat->name() + "_pos_vel" + s_para + ".dat";
	dat_pos_vel.open(s_pos_vel, ios::out | ios::trunc);

	dat_temp << "# " << poly.info() << "\n# " << thermostat->info() << endl;
	dat_temp << "# time temp epot" << endl;

	dat_pos_vel << "# " << poly.info() << "\n# " << thermostat->info() << endl;
	dat_pos_vel << "# absPosition velocity force relPosition" << endl;
	
	int index_to_flush = 64E6 / 64;
	// Simulation
	for (int i = 0; i < para_warm; ++i) thermostat->propagate();
	cout << "Warmlauf abgeschlossen" << endl;

	int index_print{ (int)(para_runs * 4E-1) };
	int index_to_file{ (int)para_aus };
	for (int i = 0; i < para_runs; i++) {
		if (!(i % index_to_file)) {
			dat_temp << i*para_dtime;
			dat_temp << " " << poly.calculate_temp();
			dat_temp << " " << poly.update_epot() << '\n';
			dat_pos_vel << poly;
			if ( ! (i % index_to_flush) ) {
				dat_temp << flush;
				dat_pos_vel << flush;
			}
		}

		if (!(i % index_print)) {
			cout << i*para_dtime << endl;
			cout << "Ekin: " << poly.update_ekin() << endl;
			cout << "T: " << poly.calculate_temp() << endl;
		}
		thermostat->propagate();
	}
	dat_temp << flush;
	dat_pos_vel << flush;
	delete thermostat;

	cout << "<< Die Datei '" << s_temp << "' wurde erstellt." << endl;
	cout << "<< Die Datei '" << s_pos_vel << "' wurde erstellt." << endl;

	dat_temp.close();
	dat_pos_vel.close();
	return 0;
}

