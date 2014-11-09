#include<iostream>
#include<fstream>
#include<stdlib.h>
#include "Monomer.h"
#include "Functions.h"
#include "Thermostat_None.h"
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
	double q = p_a.monomers.size()*p_a.target_temperature()*ref_time / 1E-14;
	cout << "q = " << q << endl;
	//Thermostat_None thermostat(p_a, 1E-15 / ref_time);
	//Nose_Hoover thermostat(p_a, q, step);  
	Nose_Hoover thermostat(p_a, q, step);
	MyFile.open("Nose_Hoover.dat", ios::out | ios::trunc);
	MyFile2.open("NH_pos_vel_p=4_T=20.dat", ios::out | ios::trunc);

	for (int i = 0; i < 1E9; i++) {
		if (!(i % (int)1E3)) {
			cout << endl << i << endl;
			//cout << endl << p_a;
			cout << "Ekin: " << p_a.update_ekin() << endl;
			cout << "T: " << p_a.calculate_temp() << endl;
			MyFile << i*step << " " << p_a.calculate_temp() << endl;
			double av_velocity = 0.0;
			for (auto& m : p_a.monomers) av_velocity += m.velocity;
			av_velocity /= p_a.monomers.size();
			for (unsigned int i = 1; i <= p_a.monomers.size(); i++) {
				MyFile2 << p_a.monomers[i].position - p_a.monomers[i - 1].position << " " << p_a.monomers[i].velocity - av_velocity << endl;
			}
			MyFile2 << p_a.monomers[0].position - p_a.monomers.back().position << " " << p_a.monomers[0].velocity - av_velocity << endl;
		}
		thermostat.propagate();
	}
	MyFile.close();
	MyFile2.close();
	cout << endl << p_a;
	cout << "Ekin: " << p_a.update_ekin() << endl;
	cout << "T: " << p_a.calculate_temp() << endl;

	return 0;
}
