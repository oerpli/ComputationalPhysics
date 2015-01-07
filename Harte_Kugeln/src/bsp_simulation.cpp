#include <iostream>
#include <vector>
#include <functional>

#include "MatVec.h"
#include "Kugel.h"
#include "Box.h"

#include "auswertung_bsp_average_vel.h"
#include <memory>
#include "AuswertVec.h"

using namespace std;

int main() {
	const unsigned DIM {3}; //TODO: kann abhängig von Eingabe sein
	AuswertVec<Kugel<DIM>> vec_unary;
	AuswertVec<Kugel<DIM>,Kugel<DIM>> vec_binary;

	{//TODO: kann abhängig von Eingabe sein
		vec_unary.push_back( new auswertung_bsp_average_vel<DIM> );
		vec_unary.push_back( new auswertung_bsp_average_vel<DIM> );
	}
	MatVec<lengthT,DIM> box_size{10*m, 10*m, 10*m}; //TODO: kann abhängig von Eingabe sein
	Kugel<DIM> kugel1{.5 * kg, .5 * m}; //TODO: kann abhängig von Eingabe sein
	MatVec<velocityT,DIM> vel{14*mps};
	kugel1.velocity(vel);
	Box<DIM> box{box_size, 10, kugel1}; //TODO: kann abhängig von Eingabe sein

	//TODO: Warmlauf einfügen

	timeT ausw_time{}, d_ausw_time{13*s};
	timeT next_ausw_time = ausw_time + d_ausw_time;
	timeT d_time{}, zero_time{};

	box(vec_unary,vec_binary);
	vec_unary.print_result(cout);
	cout << '\n';
	vec_binary.print_result(cout);
/*
	unsigned max_collisions{100}; //TODO: kann abhängig von Eingabe sein
	for (unsigned i = 0; i < max_collision; ++i) {
		box.next_collision(); //update next_collision_time in absolute_time

		while ( (d_time = box.next_collision_time() - next_ausw_time) > zero_time) {
			box.fast_forward(d_time);
			box(vec_unitaryF, vec_binaryF);
		}
	}
*/
}
