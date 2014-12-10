#include <iostream>
#include <cmath>

#include "Vec3D.h"

using namespace std;

int main() {
	double ar[3]={1,3,2};
	Vec3D <double> v1{2,3,-1}, v2{ar}, v3, v4;
	
	cout << "v1{2,3,-1}: " << endl << v1 << endl;
	cout << "v2{ar}: " << endl << v2 << endl;
	v3=v1;
	cout << "v3=v1: " << endl << v3  << endl;
	cout << "(v3==v1): " << endl << (v3==v1) << endl;
	cout << "(v3==v2): " << endl << (v3==v2) << endl;
	v4=2.*v3;
	cout << "v4=2.*v3: " << endl << v4 << endl;
	cout << "v3-v4: " << endl << v3-v4 << endl;
	cout << "-v3: " << endl << -v3 << endl;
	cout << "v3: " << endl << v3 << endl;
	v3*=2;
	cout << "v3*=2: " << endl << v3 << endl;
	cout << "v2.sum(): " << endl << v2.sum() << endl;
return 0;
}
