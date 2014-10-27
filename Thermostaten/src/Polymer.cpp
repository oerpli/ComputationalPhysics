#include "Polymer.h"

#include<cmath>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>

void Polymer::Initiate_monomer_array(const int size, double pos, double vel) {
	Monomers = std::vector<Monomer>();

	if (pos != 0 && vel != 0){
		for (auto& m : Monomers){
			m.Position = rand() % 5;
			m.Position = 0;
		}
	}
}

void Polymer::Initiate_polymer_std() {
	Temp_soll = 0;
	Ekin = Epot = 0;
}


Polymer::Polymer(int length) {
	Initiate_polymer_std();
	Initiate_monomer_array(length, 0, 0);
}

Polymer::~Polymer() {}

std::ostream & Polymer::Print(std::ostream &os) const {
	for (auto& m : Monomers) {
		m.Print(os);
		os << std::endl;
	}
	return os;
}

/*
double Polymer::Force(double r) {//LJ
double s=1, e=1, sr6=pow(s/r,6);
if (r==0)
return 0;
return -24 * e*(2 * pow(sr6, 2) / r - sr6 / r);
}
*/

double Polymer::Force(double r) {//LJ
	double k = 1;
	return r*k;
}

void Polymer::Update_Force() {
	double force_buf = 0;
	unsigned int size = Monomers.size();
	//wahrscheinlich durch Optimierung der nächsten Schleife unnötig
	for (auto& m : Monomers){
		m.Force = 0;
	}
	for (unsigned int i = 1; i <= size; i++) {
		force_buf = Force(Monomers[i - 1] - Monomers[i % size]);
		Monomers[i - 1].Force += force_buf; //bin mir da mit dem Vorzeichen nicht sicher!
		Monomers[i % size].Force -= force_buf;
	}
}

void Polymer::Update_EKin(){
	Ekin = 0.0;
	for (auto& m : Monomers) {
		Ekin += m.Velocity*m.Velocity; //mass = 1 
	}
	Ekin /= 2.0;
}


//void Polymer::Next_position(double dt){
//	for (int i = 0; i < A_length; i++)
//		A_monomer[i].Next_position(dt);
//}
//
//void Polymer::Next_velocity(double dt){
//	for (int i = 0; i < A_length; i++)
//		A_monomer[i].Next_velocity(dt);
//}
//
//int Polymer::Get_length() { return A_length; }
//
//double Polymer::Get_ekin() { return Ekin; }
//Polymer::Polymer() {
//	Initiate_polymer_std();
//	Initiate_monomer_array(0, 0);
//}
//Polymer::Polymer(int len, double pos, double vel) {
//	Initiate_polymer_std();
//	A_length = len;
//	Initiate_monomer_array(pos, vel);
//}
//
//double Polymer::Get_monomer_position(int index) { return A_monomer[index].Get_position(); }
//
//double Polymer::Get_monomer_velocity(int index) { return A_monomer[index].Get_velocity(); }
//
//double Polymer::Get_monomer_force(int index) { return A_monomer[index].Get_force(); }
//
//
//void Polymer::Set_monomer_position(int index, double pos) { A_monomer[index].Set_position(pos); }
//
//void Polymer::Set_monomer_velocity(int index, double vel) { A_monomer[index].Set_velocity(vel); }
//
//int		Polymer::Get_position(double *& array) const {
//	if (array != 0)
//		delete[] array;
//	array = new double[A_length];
//	for (int i = 0; i < A_length; i++)
//		array[i] = A_monomer[i].Get_position();
//	return A_length;
//}
//
//int		Polymer::Get_velocity(double *& array) const {
//	if (array != 0)
//		delete[] array;
//	array = new double[A_length];
//	for (int i = 0; i < A_length; i++)
//		array[i] = A_monomer[i].Get_velocity();
//	return A_length;
//}
//
//int		Polymer::Get_force(double *& array) const {
//	if (array != 0)
//		delete[] array;
//	array = new double[A_length];
//	for (int i = 0; i < A_length; i++)
//		array[i] = A_monomer[i].Get_force();
//	return A_length;
//}
//
//void	Polymer::Set_position(double *& array, int length) {
//	if (length != A_length)
//		return;
//	for (int i = 0; i < length; i++)
//		A_monomer[i].Set_position(array[i]);
//	return;
//}
//
//void	Polymer::Set_velocity(double *& array, int length) {
//	if (length != A_length)
//		return;
//	for (int i = 0; i < length; i++)
//		A_monomer[i].Set_velocity(array[i]);
//	return;
//}
