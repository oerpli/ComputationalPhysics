#include "Thermostat.h"
#include "Stat.h"
#include "Histo.h"
#include "Nose_Hoover_Chain.h"
#include "Andersen.h"
#include "Lowe_Andersen.h"
#include "Gaussian.h"
#include "Nose_Hoover.h"
#include "Thermostat_None.h"
#include "Berendsen.h"
#include "Bussi.h"

#include <vector>
#include "Stat.h"
#include "Histo.h"
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

double width_normal(double sigma2, int n, int a) {
	return sqrt( abs ( sigma2 * log( M_PI * sigma2 * a * n ) ) );
}

/* ######################### */
int main(int argc, char* argv[]) {
	//default für  p,runs,warmlauf,hist,Temp,dtime,ausgabe   :jedes xte wird ausgegeben
	double a_para[]{64, 1E9, 1E8, 500, 20, 1E-15, 1};
	double para_p, para_temp, para_dtime, para_runs, para_warm, para_aus, para_hist;
	int			i_para{ 1 };
	string s_para{};
	string	s_histo{};
	ofstream dat_histo{};
	Thermostat *thermostat{};
	vector<Histo> v_histo;
	
	// Bestimmen der Parameter zur Initialisierung von Poly und Thermostat
	for (i_para = 1; i_para < min(7, argc); ++i_para) {
		if (is_number(argv[i_para])) a_para[i_para - 1] = stod(argv[i_para]);
		else break;
	}
	para_p = a_para[0];
	para_temp = a_para[4];
	para_dtime = a_para[5] / ref_time;
	para_runs = a_para[1];
	para_warm = a_para[2];
	para_aus = a_para[6];
	para_hist = a_para[3];
	
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
		  double q_def{ poly.monomer_mass*poly.target_temperature()/poly.feder_konst() };
			double q{ set_param(q_def * poly.monomers.size() , argv, argc, i_thermos + 1) };
			double q2{ set_param( q_def , argv, argc, i_thermos + 2 ) };
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

	s_histo = thermostat->name() + "_histo" + s_para + ".dat";
	dat_histo.open(s_histo, ios::out | ios::trunc);

	dat_histo << "# " << poly.info()  << "\n# " << thermostat->info() << endl;
	dat_histo << "# velocity relPosition" << endl;
	
	v_histo.resize(2);
	double sigma2=poly.target_temperature() / poly.monomer_mass;
	double width=width_normal(sigma2,para_hist,para_runs*1E-5);
cout << sigma2 << "  " << width << endl;
	v_histo[0].set(para_hist, width);
	sigma2=poly.target_temperature() / poly.feder_konst();
	v_histo[1].set(para_hist, width_normal(sigma2,para_hist,para_runs*1E-5));
	
	// Simulation
	for (int i = 0; i < para_warm; ++i) thermostat->propagate();
	cout << "Warmlauf abgeschlossen" << endl;

	int index_print{ (int)(para_runs * 4E-1) };
	int index_to_file{ (int)para_aus };
	for (int i = 0; i < para_runs; i++) {
		if (!(i % index_to_file)) {
				auto mi = poly.monomers.begin(), mj = poly.monomers.begin();
				auto mend = poly.monomers.end();
				for (++mj; mi != mend; ++mi, ++mj) {
					if (mj == mend) mj = poly.monomers.begin();
					v_histo[0].add( mi->velocity );
					v_histo[1].add( *mj - *mi );
				}
		}

		if (!(i % index_print)) {
			cout << i*para_dtime << endl;
			cout << "Ekin: " << poly.update_ekin() << endl;
			cout << "T: " << poly.calculate_temp() << endl;
		}
		thermostat->propagate();
	}
	delete thermostat;

	for (auto& h : v_histo) h.norm();
	dat_histo << v_histo;
	
	dat_histo.close();
	cout << "<< Die Datei '" << s_histo << "' wurde erstellt." << endl;
	return 0;
}

