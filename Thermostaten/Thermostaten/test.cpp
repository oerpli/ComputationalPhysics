#include "Monomer.h"
#include "Functions.h"
#include "Thermostate.h"

#include<iostream>
#include<stdlib.h>

using namespace std;

int main() {

	cout << "Hello World" << endl;
	
	Polymer p_a(3,1,3);
	
	cout << rand()%5 << endl;

	cout << endl;
	cout << p_a << endl;
	cout << "calculation" << endl;
	Thermos_none(p_a,1);
	cout << p_a << endl;
return 0;
}
