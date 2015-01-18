#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <memory>


#include "MatVec.h"
#include "Kugel.h"
#include "Box.h"

#include "AuswertVec.h"
#include "auswertung_bsp_average_vel.h"
#include "auswertung_bsp_average_energy.h"

#include "PairDistribution.h"
#include "auswertung_collision_time.hpp"

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

	lengthT box_length {(2.*radius*Pow(double(N)/density, 1, 3))*m};
	//density = N*pow(radius*2./box_length, 3);

	AuswertVec<Kugel<DIM>> vec_unary;
	AuswertVec<Kugel<DIM>,Kugel<DIM>,lengthT> vec_binary;
	auswertung_collision_time<DIM> ausw_coll_time{.0005};

	MatVec<lengthT,DIM> box_size{box_length, box_length, box_length}; //TODO: kann abhängig von Eingabe sein
	Kugel<DIM> kugel1{mass, radius}; //TODO: kann abhängig von Eingabe sein
	MatVec<velocityT,DIM> vel{14};
	kugel1.velocity(vel);
	Box<DIM> box{box_size, N, kugel1}; //TODO: kann abhängig von Eingabe sein


	{//TODO: kann abhängig von Eingabe sein
		vec_unary.push_back( new auswertung_bsp_average_vel<DIM>{} );
		vec_unary.push_back( new auswertung_bsp_average_energy<DIM>{} );
		vec_binary.push_back(new PairDistribution<DIM> { histo_width, density, N });
	}

	stringstream ss_para{};
	string name_pair_dist{};
	ofstream dat_pair_dist{}, dat_coll_time{};

	ss_para.precision(0);
	ss_para << "_DIM" << DIM;
	ss_para << "_N" << N;
	ss_para << "_r" << (double)radius;
	ss_para << "_m" << (double)mass;
	ss_para << "_rho" << (double)density;
	ss_para << "_run" << scientific << (double)simulation_time;


	name_pair_dist = "Pair_distribution" + ss_para.str() + ".dat";
	dat_pair_dist.open(name_pair_dist, ios::out | ios::trunc);
	const CollisionPair<DIM> &cp = box.collision_pair();
	unsigned count_no_coll { }, count_coll{ };


	cout << "Dimension:\t" << DIM << '\n';
	cout << "Density:\t" << density << '\n';
	cout << "Number of Spheres:\t" << N << '\n';
	cout << "Boxlänge:\t" << box_length << '\n';
	cout << "Radius:\t" << radius << '\n';
	cout << "Warmlauf:\t" << warm_time << '\n';
	cout << "Gesamte Simulationszeit:\t" << simulation_time + warm_time << '\n';
	cout << "Auswertung alle\t" << ausw_t_step << '\n';
	cout << "Histogrammgenauigkeit:\t" << histo_width << '\n';


	cout << "\n\nSTART SIMULATION\n" << endl;

	if (! box.initiate()) {
		cout << "Zu viele Kugeln für Box.";
		return 1;
	}
	ausw_coll_time( box.collision_pair() );
/*
	box.unitary(vec_unary);
	vec_unary.print_result(cout);
	cout << flush;
*/

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
		ausw_coll_time( box.collision_pair() );
//		cout << coll_time << '\n';
		++count_coll;
	}
/*
	cout << "\nNach Warmlauf\n\n";
	box.print(cout);
	cout << '\n';
*/

	cout << "Time: " << box.time() << endl;
/*	box(vec_unary,vec_binary);
	vec_unary.print_result(cout);
	cout << '\n' << "vec_binary: ";
	vec_binary.print_result(cout);
*/
	//TODO: kann abhängig von Eingabe sein
	timeT ausw_t_next{ausw_t_step};
	timeT simulation_end{simulation_time + box.time()};
	while (box.time() <= simulation_end){
		while ( ausw_t_next < box.next_event() ) {
			box.fast_forward(ausw_t_next);
			ausw_t_next = ausw_t_step;
			box(vec_unary, vec_binary);
		}
		if (! cp) ++count_no_coll;
		ausw_t_next -= box.collide();
		ausw_coll_time( box.collision_pair() );
		++count_coll;
	}

	cout << "Time: " << box.time() << '\n';
	vec_unary.print_result(cout);

	vec_binary.print_result(dat_pair_dist);

	dat_coll_time.open("Coll_time" + ss_para.str() + ".dat", ios::out | ios::trunc);
	ausw_coll_time.print_result(dat_coll_time);

	cout << "\n no collision: " << count_no_coll;
	cout << " of " << count_coll << " collisions";
	cout << "  => " << count_no_coll * 100. / count_coll << "%\n";
}
