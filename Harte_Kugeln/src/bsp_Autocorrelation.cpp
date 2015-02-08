#include <iostream>
#include <vector>

#include "Autocorrelation_Box.hpp"
#include "Kugel.h"
#include "Rand.h"

template<typename T, unsigned DIM>
MatVec<T,DIM> make_rand_vec(double min = 0., double max = 1.) {
	MatVec<T,DIM> result{};
	result([&](T& t){ t = T(Rand::real_uniform(min,max)); });
	return result;
}

using namespace std;

int main() {
	const unsigned DIM{3};

	size_t nruns{3};
	unsigned nkugel { 1809 };
	vector<Kugel<DIM>> vec_kugel(nkugel,Kugel<DIM>{});
	auto iter = vec_kugel.begin(), it_end = vec_kugel.end();

	size_t n_autocorr{1000};
	Autocorrelation_Box<DIM> autocorr{n_autocorr};

MatVec<velocityT,DIM> vel_buf{};

	for (size_t runs{0}; runs < nruns; ++runs) {
		for (iter = vec_kugel.begin(); iter != it_end; ++iter) {
			vel_buf = make_rand_vec<velocityT,DIM>(-1., 1.);
//			cout << vel_buf << '\n';
			iter->velocity( vel_buf );
			autocorr(*iter);
		}
	}

	cout << autocorr << '\n';
	cout << "done\n";
}
