#include<iostream>
#include<fstream>
#include<stdlib.h>
#include "Monomer.h"
#include "Functions.h"
#include "Thermostat_None.h"
#include "Andersen.h"
#include "Lowe_Andersen.h"
#include "Nose_Hoover.h"
#include "Nose_Hoover_Chain.h"
#include "consts.h"

using namespace consts;
using namespace std;

int main() {
	ofstream MyFile;
	ofstream MyFile2;
	cout << "Hello World" << endl;
	Polymer p_a(4, 20);
	p_a.initiate_monomers_random();
	cout << "T vor skalierung: " << p_a.ekin / p_a.monomers.size() / (0.5*ref_k) << endl;

	cout << "T nach skalierung: " << p_a.calculate_temp() << endl;
	double step = 1E-15 / ref_time;
	cout << "step = " << step << endl;
	Lowe_Andersen thermostat(p_a, step, 1./4./step);
	cout << "Lowe_Andersen" << endl;
	MyFile.open("Lowe_Andersen_temp_p4_T20.dat", ios::out | ios::trunc);
	MyFile2.open("Lowe_Andersen_pos_vel_p4_T20.dat", ios::out | ios::trunc);


	double av_velocity = 0.0;
	int runs=(int) 1E6;
	for (int i = 0; i < runs; i++) {
		MyFile << i*step << " " << p_a.calculate_temp() << endl;
		if (!(i % (int)(runs*1E-2))) {
			cout << endl << i << endl;
			//cout << endl << p_a;
			cout << "Ekin: " << p_a.update_ekin() << endl;
			cout << "T: " << p_a.calculate_temp() << endl;
			av_velocity = 0.0;
			for (auto& m : p_a.monomers) av_velocity += m.velocity;
			av_velocity /= p_a.monomers.size();
		}
		for (unsigned int i = 1; i <= p_a.monomers.size(); i++) {
			MyFile2 << p_a.monomers[i].position - p_a.monomers[i - 1].position << " " << p_a.monomers[i].velocity - av_velocity << endl;
		}
		MyFile2 << p_a.monomers[0].position - p_a.monomers.back().position << " " << p_a.monomers[0].velocity - av_velocity << endl;
		thermostat.propagate();
	}
	MyFile.close();
	MyFile2.close();
	cout << endl << p_a;
	cout << "Ekin: " << p_a.update_ekin() << endl;
	cout << "T: " << p_a.calculate_temp() << endl;

	return 0;
}
