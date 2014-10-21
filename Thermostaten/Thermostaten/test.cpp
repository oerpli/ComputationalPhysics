#include "Monomer.h"
#include "Functions.h"

#include<iostream>

using namespace std;




int main() {

	cout << "Hello World" << endl;
	
	Monomer a, b(1,3);
	
	cout << a.Get_position() << " " << b.Get_position() << endl;
	b.Print(cout);
	cout << endl;

	cout << a << endl;
return 0;
}
