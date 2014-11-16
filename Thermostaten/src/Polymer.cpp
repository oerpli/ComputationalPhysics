#include "Polymer.h"
#include "consts.h"
#include "Rand.h"
#include<algorithm>
#include<cmath>
#include<iostream>
#include<stdlib.h>
#include<vector>
using namespace consts;
using namespace std;

void Polymer::initiate_monomers_random() {
	double av_velocity = 0.0;
	for (auto& m : monomers) {
		m.velocity = Rand::real_uniform() - 0.5;
		av_velocity += m.velocity;
	}
	av_velocity /= monomers.size();
	for (auto& m : monomers) m.velocity -= av_velocity;
	update_ekin();
	double scale_factor = sqrt(target_temperature()*monomers.size() / ekin*0.5);
	for (auto& m : monomers) m.velocity *= scale_factor;
}

void Polymer::initiate_monomers_one() { //erstes Monomer großteil der Energie
	double max_vel = sqrt((monomers.size() - 1)*target_temperature() / monomer_mass);
	double speed = -max_vel / (monomers.size() - 1);
	for (auto& m : monomers) m.velocity = speed;
	monomers[0].velocity = max_vel;
}

Polymer::Polymer(unsigned length, double temperature)
	: epot(0)
	, monomer_mass(2. / length)
	, monomers(std::vector<Monomer>(length, Monomer(0.0, 0.))) {
	target_temperature(temperature);
}

Polymer::~Polymer() {}

double Polymer::feder_konst() const { return m_feder_konst; }

double Polymer::target_temperature() const { return m_target_temp; }

void Polymer::target_temperature(double temperature) {
	m_target_temp = temperature*ref_k;
	m_feder_konst = monomer_mass * pow(monomers.size() * m_target_temp / ref_hbar, 2);
}

std::ostream & Polymer::print(std::ostream &os) const {
	auto mi = monomers.begin(), mj = monomers.begin(), mend = monomers.end();
	++mj;
	for (; mi != mend; ++mi, ++mj) {
		if (mj == monomers.end()) mj = monomers.begin();
		print_m(*mi, os);
		os << "  " << *mj - *mi << std::endl;
	}
	return os;
}

double Polymer::force(double r) const { return -r*m_feder_konst; }

void Polymer::update_forces() {
	for (auto& m : monomers) m.force = 0;
	unsigned int size = monomers.size();
	for (unsigned int i = 1; i <= size; i++) {
		double force_buf = force(monomers[i - 1] - monomers[i % size]);
		monomers[i - 1].force += force_buf; //bin mir da mit dem Vorzeichen nicht sicher!
		monomers[i % size].force -= force_buf;
	}
}

double Polymer::update_ekin(){
	ekin = 0.0;
	double av_velocity = 0.0;
	for (auto& m : monomers) av_velocity += m.velocity;
	av_velocity /= monomers.size();
	for (auto& m : monomers) ekin += pow(m.velocity - av_velocity, 2);
	ekin *= monomer_mass*0.5;
	return ekin;
}

double Polymer::update_epot() {
	auto mi = monomers.begin(), mj = monomers.begin(), mend = monomers.end();
	++mj;
	epot=0;
	for (; mj != mend; ++mi, ++mj) epot += pow(*mj - *mi , 2);
	mj = monomers.begin();
	epot += pow(*mj - *mi , 2);
	return epot *= m_feder_konst;
}

double Polymer::calculate_temp() const {
	double av_velocity = 0, av_energy = 0;
	for (auto& m : monomers) av_velocity += m.velocity;
	av_velocity /= monomers.size();
	for (auto& m : monomers) av_energy += pow(m.velocity - av_velocity, 2);
	av_energy *= monomer_mass / 2 / monomers.size();
	return av_energy / (0.5*ref_k);
}

