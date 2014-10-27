#ifndef Thermostate_H
#define Thermostate_H

#include "Polymer.h"

#include<cmath>

void Thermos_none(Polymer & poly, double time) {
	 //kein Thermostat Verlet
	//poly.Calculate_force();
	//poly.Next_velocity(time / 2);
	//poly.Next_position(time);
	//poly.Calculate_force();
	//poly.Next_velocity(time / 2);
} //Thermos_none

#endif
