#define _USE_MATH_DEFINES
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

inline string& remove_special(string& str) {
	return str.erase(str.find("+"), 1);
}

double width_normal(double sigma2, int n, int a) {
	return sqrt(abs(2 * sigma2 * log(sqrt(M_PI_2 * sigma2) * a)));
}

void statistic_add(double val, unsigned index, vector<Histo>& v_h, vector<Stat>& v_s) {
	if (index >= v_h.size()) return;
	v_h[index].add(val);
	v_s[index].add(val);
}

/* ######################### */
int main(int argc, char* argv[]) {
	//default für  runs,warmlauf,dtime,p,Temp,hist,ausgabe   :jedes xte wird ausgegeben
	double a_para[]{1E8, 1E7, 1E-15, 64, 20, 1000, 1};
	
	double para_p, para_temp, para_dtime, para_runs, para_warm, para_aus, para_hist;
	int a_para_size = sizeof(a_para) / sizeof(*a_para);
	int			i_para{ 1 };
	stringstream ss_para;
	string	s_histo{};
	ofstream dat_histo{};
	Thermostat *thermostat{};
	vector<Histo> v_histo;
	vector<Stat> v_stat;

	// Bestimmen der Parameter zur Initialisierung von Poly und Thermostat
	for (i_para = 1; i_para < min(a_para_size + 1, argc); ++i_para) {
		if (is_number(argv[i_para])) a_para[i_para - 1] = stod(argv[i_para]);
		else break;
	}
	para_p = a_para[3];
	para_temp = a_para[4];
	para_dtime = a_para[2] / ref_time;
	para_runs = a_para[0];
	para_warm = a_para[1];
	para_aus = a_para[6];
	para_hist = a_para[5];

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
			double q_def{ poly.monomers.size()*poly.target_temperature()*ref_time / 1E-13 };
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
	cout << "Trotter Zahl:\t" << poly.monomers.size() << endl;
	cout << "Initierung:\t" << poly.ini() << endl;
	cout << "Zeitschritt:\t" << para_dtime << endl;
	cout << "Sim. Laenge:\t" << para_runs << endl;
	cout << "Warmlaufzeit:\t" << para_warm << endl;
	
	ss_para.precision(0);
	ss_para << "_p" << (int)para_p;
	ss_para << "_T" << (int)para_temp;
	ss_para << "_run" << scientific << para_runs;
	ss_para << "_" << poly.ini();

	s_histo = thermostat->name() + "_histo" + ss_para.str() + ".dat";

	v_stat.resize(7);
	v_histo.resize(7);
	double sigma2 = poly.target_temperature() / poly.monomer_mass;
	v_histo[0].set(para_hist, 5 * sqrt(sigma2));  // velocity
	sigma2 = poly.target_temperature() / poly.feder_konst();
	v_histo[1].set(para_hist, 5 * sqrt(sigma2));  // relPosition
	sigma2 = 2.5 * pow(ref_k * para_temp, 2);
	v_histo[2].set(para_hist, .0, 150.); // temp
	v_histo[3].set(para_hist, 5); // absPosition
	v_histo[4].set(para_hist, 0., 100.); // epot
	v_histo[5].set(para_hist, 5); // schwerPos
	sigma2 = poly.target_temperature() / poly.monomer_mass;
	v_histo[6].set(para_hist, 5 * sqrt(sigma2));  // schwerVel
	
	// Simulation
	long long onepercent = para_warm / 100;
	int percent = 0;
	for (long long i = 0; i < para_warm; ++i){
		if (!(i%onepercent)) cout << ++percent << "%\r" << flush;
		thermostat->propagate();
	}
	cout << endl << "Warmlauf abgeschlossen" << endl;

	onepercent = para_runs / 100;
	percent = 0;
	int index_to_file{ (int)para_aus };
	for (long long i = 0; i < para_runs; i++) {
		if (!(i%onepercent)) cout << ++percent << "%\r" << flush;
		if (!(i % index_to_file)) {
			auto mi = poly.monomers.begin(), mj = poly.monomers.begin();
			auto mend = poly.monomers.end();
			for (++mj; mi != mend; ++mi, ++mj) {
				if (mj == mend) mj = poly.monomers.begin();
				statistic_add(mj->position, 3, v_histo, v_stat);
				statistic_add(mi->velocity, 0, v_histo, v_stat);
				statistic_add(*mj - *mi, 1, v_histo, v_stat);
			}
			statistic_add(poly.calculate_temp(), 2, v_histo, v_stat);
			statistic_add(poly.update_epot(), 4, v_histo, v_stat);
			statistic_add(poly.update_position(), 5, v_histo, v_stat);
			statistic_add(poly.velocity, 6, v_histo, v_stat);
		}

		thermostat->propagate();
	}
	cout << endl;

	dat_histo.open(remove_special(s_histo), ios::out | ios::trunc);

	dat_histo << "# " << poly.info() << "\n# " << thermostat->info() << endl;
	dat_histo << "# " << "runs " << para_runs << " warm " << para_warm << endl;
	dat_histo << "# velocity 1 relPos 3 tempCol 5 absPosition 7 epot 9";
	dat_histo << " schwerPos 11 schwerVel 13" << endl;

	dat_histo << "# " << scientific;
	for (auto& stat : v_stat) {
		stat.calc();
		dat_histo << stat.mu << " " << stat.sigma << " ";
	}
	dat_histo << endl;

	for (auto& h : v_histo) h.norm();
	dat_histo << v_histo;

	dat_histo << flush;
	dat_histo.close();

	cout << "<< Die Datei '" << s_histo << "' wurde erstellt." << endl;
	delete thermostat;
	return 0;
}

