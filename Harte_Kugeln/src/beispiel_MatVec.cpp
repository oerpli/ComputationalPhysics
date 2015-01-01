#include <iostream>
#include <vector>
#include <algorithm>

#include <typeinfo>

#include "MatVec.h"
#include "Kugel.h"

using namespace std;


// Vectoren elementweise mulitiplizieren
// Scilab: vec1.*vec2

int main() {
	// erzeugt einen Vektor der, so weit wie möglich,
	// mit den Übergabewerten befüllt ist,
	// der Rest wird mit 0 aufgefüllt
	MatVec<lengthT, 3> lengthVec {2 * m, 3 * m, 1 * m};

	// erzeugt einen Vektor befüllt mit 3*N
	MatVec<forceT, 3> forceVec (3 * N);

	// wird behandelt wie {1*N, 0*N, 0*N}
	MatVec<forceT, 3> forceVec1 {1 * N};

	cout << "forceVec (3 * N):\n" << forceVec << '\n';
	cout << "forceVec1 {1 * N}:\n" << forceVec1 << '\n';

	cout << "lengthVec {2 * m, 3 * m, 1 * m}:\n";
	for (auto& el : lengthVec) cout << el << ", "; //range based loops sind verwendbar
	cout << '\n';
	cout << "norm2: " << lengthVec.norm2() << "  norm: " << lengthVec.norm() << '\n';

	cout << "forceVec * lengthVec:\n" << forceVec * lengthVec << '\n';

	const unsigned dim {3};
	cout << '\n' << "Kugelbeispiele mit Dimension " << dim << ":" << '\n';

	MatVec<velocityT, dim> velVec {2 * mps, -1 * mps, 3 * mps};

	Kugel<dim> k1{}, k2{ (3 * kg),(.5 * m)};
	k2.velocity(velVec); // setzt velocity von k2 auf die Werte von velVec

	Kugel<dim> k3{k2};
	cout << '\n' << "k1 Standard:" << '\n';
	k1.print();

	cout << '\n' << "k2:" << '\n';
	k2.print();
	cout << "VelVec:   " << k2.velocity() << '\n';

	cout << '\n' << "k3 Copy k2:" << '\n';
	k3.print();

}
