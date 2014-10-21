#include "Monomer.h"
#include "Functions.h"
#include "Thermostate.h"

#include<iostream>
#include<stdlib.h>

using namespace std;

int main() {

	cout << "Hello World" << endl;
<<<<<<< a978db21cce4976d575a5e942d124bea1220d57c

	Polymer p_a(3, 1, 3);

	cout << rand() % 5 << endl;
=======
	
	Polymer p_a(5,1,3);
	
	cout << rand()%5 << endl;
>>>>>>> e5c34e90663e99905fd195e57d38f3c2e3eb52f5

	cout << endl;
	cout << p_a << endl;
	cout << "calculation" << endl;
	Thermos_none(p_a, 1);
	cout << p_a << endl;
<<<<<<< a978db21cce4976d575a5e942d124bea1220d57c
	return 0;
=======
	
return 0;
>>>>>>> e5c34e90663e99905fd195e57d38f3c2e3eb52f5
}
