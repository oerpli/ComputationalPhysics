#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>


#include "MatVec.h"
#include "Kugel.h"
#include "Box.h"

#include "auswertung_bsp_average_vel.h"
#include "auswertung_bsp_average_energy.h"
#include "PairDistribution.h"
#include <memory>
#include "AuswertVec.h"

using namespace std;

bool is_number(const string &str) {
	return str.find_first_not_of(".eE-0123456789") == string::npos;
}


int main(int argc, char* argv[]) {

	const unsigned DIM {3};

	//default Parameter: Dichte, Kugelanzahl, Kugelradius, Masse, Zeit runs, Zeit Warmlauf, Zeit Auswertung, Histogrammbreite
	double a_para[] {0.2, 108, 1.0, 1.0, 1E3, 1E2, 1E-1, 1E-1};
	int a_para_size = sizeof(a_para) / sizeof(*a_para);
	int i_para {1};

	for (i_para = 1; i_para < min(a_para_size + 1, argc); i_para++) {
		if (is_number(argv[i_para])) a_para[i_para - 1] = stod(argv[i_para]);
		else break;
	}

 //TODO: kann abhängig von Eingabe sein
	dimlessT density {a_para[0]};
	unsigned N {(unsigned)a_para[1]};
	lengthT radius {a_para[2]*m};
	massT mass {a_para[3]*kg};
	timeT simulation_time {a_para[4]*s};
	timeT warm_time {a_para[5]*s};
	timeT ausw_t_step {a_para[6]*s};
	double histo_width {a_para[7]};

	lengthT box_length {ceil(2.*radius.value()*pow(N/(density.value()), 1./3.))*m};
	density = N*Pow(radius*2./box_length, 3);

	cout << "Dimension:\t" << DIM << endl;
	cout << "Density:\t" << density << endl;
	cout << "Number of Spheres:\t" << N << endl;
	cout << "Boxlänge:\t" << box_length << endl;
	cout << "Radius:\t" << radius << endl;
	cout << "Warmlauf:\t" << warm_time << endl;
	cout << "Gesamte Simulationszeit:\t" << simulation_time + warm_time << endl;
	cout << "Auswertung alle\t" << ausw_t_step << endl;
	cout << "Histogrammgenauigkeit:\t" << histo_width << endl;


	AuswertVec<Kugel<DIM>> vec_unary;
	AuswertVec<Kugel<DIM>,Kugel<DIM>> vec_binary;


	MatVec<lengthT,DIM> box_size{box_length, box_length, box_length}; //TODO: kann abhängig von Eingabe sein
	Kugel<DIM> kugel1{mass, radius}; //TODO: kann abhängig von Eingabe sein
	MatVec<velocityT,DIM> vel{14*mps};
	kugel1.velocity(vel);
	Box<DIM> box{box_size, N, kugel1}; //TODO: kann abhängig von Eingabe sein


	{//TODO: kann abhängig von Eingabe sein
		vec_unary.push_back( new auswertung_bsp_average_vel<DIM> );
		vec_unary.push_back( new auswertung_bsp_average_energy<DIM> );
		vec_binary.push_back(new PairDistribution<DIM> { histo_width, box_size });
	}

	ofstream dat_pair_dist;
	dat_pair_dist.open("pair_distribution.dat", ios::out | ios::trunc);
	const CollisionPair<DIM> &cp = box.collision_pair();
	unsigned count_no_coll { }, count_coll{ };

	if (! box.initiate()) {
		cout << "Zu viele Kugeln für Box.";
		return 1;
	}

/*	cout << "\nVor Warmlauf\n\n";
	box.print(cout);
	cout << '\n';

	box(vec_unary,vec_binary);
	vec_unary.print_result(cout);
	cout << '\n' << "vec_binary: ";
	vec_binary.print_result(cout);
*/

	timeT coll_time {};

	while (box.time() <= warm_time) {
		if (! cp) ++count_no_coll;
		coll_time = box.collide();
//		cout << coll_time << '\n';
		++count_coll;
	}
/*
	cout << "\nNach Warmlauf\n\n";
	box.print(cout);
	cout << '\n';
*/
	timeT ausw_t_next{ausw_t_step};

	cout << "Time: " << box.time() << '\n';
/*	box(vec_unary,vec_binary);
	vec_unary.print_result(cout);
	cout << '\n' << "vec_binary: ";
	vec_binary.print_result(cout);
*/
	//TODO: kann abhängig von Eingabe sein
	timeT simulation_end{simulation_time + box.time()};
	while (box.time() <= simulation_end){
		while ( ausw_t_next < box.next_event() ) {
			box.fast_forward(ausw_t_next);
			ausw_t_next = ausw_t_step;
			box(vec_unary, vec_binary);
		}
		cout << box.time() << endl;
		if (! cp) ++count_no_coll;
		ausw_t_next -= box.collide();
		++count_coll;
	}

	cout << "Time: " << box.time() << '\n';
	vec_unary.print_result(cout);
	cout << '\n' << "vec_binary: ";
	vec_binary.print_result(dat_pair_dist);

	cout << "\n no collision: " << count_no_coll;
	cout << " of " << count_coll << " collisions";
	cout << "  => " << count_no_coll * 100. / count_coll << "%\n";
}
