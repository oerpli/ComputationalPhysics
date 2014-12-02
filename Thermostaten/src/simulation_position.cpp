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

string to_human(long long value) {
	long long dim = 1;
	string res{};
	
	while ( value / dim ) dim *= 1000;
	dim /= 1000;
	
	if ( dim > (int)1E9 ) return "Overflow error";
	
	res = to_string( value / dim );
	switch ( dim ) {
		case 1000:
			res += " KB";
			break;
		case (int) 1E6:
			res += " MB";
			break;
		case (int) 1E9:
			res += " GB";
			break;
		default:
		break;
	}
	return res;
}

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
	double a_para[]{1E8, 1E7, 1E-15, 64, 20, 1};
	double para_p, para_temp, para_dtime, para_runs, para_warm, para_aus;
	int a_para_size = sizeof(a_para) / sizeof(*a_para);
	int			i_para{ 1 };
	stringstream ss_para;
	string	s_position{};
	ofstream dat_position{};
	Thermostat *thermostat{};
	
	string answer{};

	bool reset_pos_vel{};
	int	index_reset_pos_vel{100};
	
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
	para_aus = a_para[5];

	cout << "Es werden etwa " << to_human ( 15 * 7./8 * (1 + para_p) * para_runs );
	cout << " an Daten prodoziert." << endl;
	cout << "Wollen sie fortfahren? (Y|n) ";
	getline(cin, answer);
	if ( answer.find("n") != string::npos || answer.find("q") != string::npos ) {
		cout << "<< Simulation wird abgebrochen." << endl;
		return 1;
	}
	
	while (i_para < argc - 1 && is_number(argv[i_para])) ++i_para;
	int i_thermos = i_para;

	while (++i_para < argc - 1 && is_number(argv[i_para])) ++i_para;
	int i_poly_init = min(argc - 1, i_para);

	while (++i_para < argc - 1 && is_number(argv[i_para])) ++i_para;
	int i_reset_pos_vel = min(argc - 1, i_para);

	Polymer poly{ static_cast<unsigned> (para_p), para_temp };
	if (strcmp(argv[i_poly_init], "one") == 0)
		poly.initiate_monomers_one();
	else
		poly.initiate_monomers_random();
		
	reset_pos_vel = (strcmp(argv[i_poly_init], "reset") == 0 || strcmp(argv[i_reset_pos_vel], "reset") == 0);
	if ( reset_pos_vel ) index_reset_pos_vel=set_param(index_reset_pos_vel, argv, argc, i_reset_pos_vel + 1);
	
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
			double couplingtime = set_param(10 * para_dtime, argv, argc, i_thermos + 1);
			thermostat = new Berendsen{ poly, para_dtime, couplingtime };
		}
		else if (strcmp(argv[i_thermos], "Bussi") == 0) {
			double couplingtime = set_param(10 * para_dtime, argv, argc, i_thermos + 1);
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
	cout << "Reset:\t\t" << (reset_pos_vel ? index_reset_pos_vel : 0) << endl;
	cout << "Zeitschritt:\t" << para_dtime << endl;
	cout << "Sim. Laenge:\t" << para_runs << endl;
	cout << "Warmlaufzeit:\t" << para_warm << endl;
	
	ss_para.precision(0);
	ss_para << "_p" << (int)para_p;
	ss_para << "_T" << (int)para_temp;
	ss_para << "_run" << scientific << para_runs;
	if (reset_pos_vel) ss_para << "_reset" << scientific << index_reset_pos_vel;
	ss_para << "_" << poly.ini();

	s_position = thermostat->name() + "_position" + ss_para.str() + ".dat";
	
	// Simulation
	long long onepercent = para_warm / 100;
	int percent = 0;
	for (long long i = 0; i < para_warm; ++i){
		if (!(i%onepercent)) cout << ++percent << "%\r" << flush;
		if ( reset_pos_vel && !(i%index_reset_pos_vel) ) poly.set_pos_vel();
		thermostat->propagate();
	}
	cout << endl << "Warmlauf abgeschlossen" << endl;

	dat_position.open(remove_special(s_position), ios::out | ios::trunc);

	dat_position << "# " << poly.info() << "\n# " << thermostat->info() << '\n';
	dat_position << "# " << "runs " << para_runs << " warm " << para_warm;
	dat_position << " reset " << (reset_pos_vel ? index_reset_pos_vel : 0) << '\n';
	dat_position << "# time 1";
	for (int i=0; i<para_p; ++i) 
	dat_position << " mono" << i+1 << " " << 3 + 2 * i;
	dat_position << '\n' << scientific;
	
	int index_to_flush{ (int) ( 1E8 / ( 15 * ( 1 + poly.monomers.size() ) ) ) }; //Ausgabe etwa alle 1E8 B
	onepercent = para_runs / 100;
	percent = 0;
	int index_to_file{ (int)para_aus };
	for (long long i = 0; i < para_runs; i++) {
		if (!(i%onepercent)) cout << ++percent << "%\r" << flush;
		if (!(i % index_to_file)) {
			dat_position << i*para_dtime;
			for (auto& monomer : poly.monomers)
			dat_position << '\t' << monomer.position;
			dat_position << '\n';
			if (!(i % index_to_flush)) dat_position << flush;
		}
		if ( reset_pos_vel && !(i%index_reset_pos_vel) ) poly.set_pos_vel();
		thermostat->propagate();
	}
	cout << endl;


	dat_position << flush;
	dat_position.close();

	cout << "<< Die Datei '" << s_position << "' wurde erstellt." << endl;
	delete thermostat;
	return 0;
}

