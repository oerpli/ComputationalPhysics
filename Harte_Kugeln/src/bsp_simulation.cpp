#include <iostream>
#include <vector>
#include <functional>

#include "MatVec.h"
#include "Kugel.h"
#include "Box.h"

#include "auswertung_bsp_average_vel.h"
#include "auswertung_bsp_average_energy.h"
#include <memory>
#include "AuswertVec.h"

using namespace std;

int main() {
	const unsigned DIM {3}; //TODO: kann abhängig von Eingabe sein
	AuswertVec<Kugel<DIM>> vec_unary;
	AuswertVec<Kugel<DIM>,Kugel<DIM>> vec_binary;

	{//TODO: kann abhängig von Eingabe sein
		vec_unary.push_back( new auswertung_bsp_average_vel<DIM> );
		vec_unary.push_back( new auswertung_bsp_average_energy<DIM> );
	}
	MatVec<lengthT,DIM> box_size{10*m, 10*m, 10*m}; //TODO: kann abhängig von Eingabe sein
	Kugel<DIM> kugel1{.5 * kg, .1 * m}; //TODO: kann abhängig von Eingabe sein
	MatVec<velocityT,DIM> vel{14*mps};
	kugel1.velocity(vel);
	Box<DIM> box{box_size, 10, kugel1}; //TODO: kann abhängig von Eingabe sein

	const CollisionPair<DIM> &cp = box.collision_pair();
	unsigned count_no_coll { }, count_coll{ };

	if (! box.initiate()) {
		cout << "Zu viele Kugeln für Box.";
		return 1;
	}
/*
	cout << "\nVor Warmlauf\n\n";
	box.print(cout);
	cout << '\n';
*/
	box(vec_unary,vec_binary);
	vec_unary.print_result(cout);
	cout << '\n';
	vec_binary.print_result(cout);

	timeT coll_time { };
	timeT warm_time {3E3 *s};
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
	timeT ausw_t_step{1*s}, ausw_t_next{ausw_t_step};

	cout << "Time: " << box.time() << '\n';
	box(vec_unary,vec_binary);
	vec_unary.print_result(cout);
	cout << '\n';
	vec_binary.print_result(cout);

	timeT simulation_time {1E5 *s}; //TODO: kann abhängig von Eingabe sein
	timeT simulation_end{simulation_time + box.time()};
	while (box.time() <= simulation_end){
		while ( ausw_t_next < box.next_event() ) {
			box.fast_forward(ausw_t_next);
			ausw_t_next = ausw_t_step;
			box(vec_unary, vec_binary);
		}
		if (! cp) ++count_no_coll;
		ausw_t_next -= box.collide();
		++count_coll;
	}

	cout << "Time: " << box.time() << '\n';
	vec_unary.print_result(cout);
	cout << '\n';
	vec_binary.print_result(cout);

	cout << "\n no collision: " << count_no_coll;
	cout << " of " << count_coll << " collisions";
	cout << "  => " << count_no_coll * 100. / count_coll << "%\n";
}
