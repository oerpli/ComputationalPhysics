#ifndef SRC_SONSTIGES_AUTOCORRELATION_BOX_HPP_
#define SRC_SONSTIGES_AUTOCORRELATION_BOX_HPP_

#include <iostream>
#include <map>

#include "Auswert.h"
#include "Autocorrelation.hpp"
#include "Kugel.h"

template<unsigned DIM>
class Autocorrelation_Box : public Auswert<Kugel<DIM>> {
private:
	using autoT = Autocorrelation<MatVec<velocityT,DIM>>;
	using vel2_type = decltype(velocityT{} * velocityT{});

	std::map<Kugel<DIM>*, autoT> map_autocorr;
	size_t m_auto_size;

	typename autoT::return_type last_value;

	std::pair<vel2_type, bool> get_value_pair() {
		Average<vel2_type> av{};
		std::pair<vel2_type, bool> pair_buf{};
		bool valid_flag{false};

		const auto iter_end = map_autocorr.end();
		for (auto iter = map_autocorr.begin(); iter != iter_end; ++iter) {
			pair_buf = (iter->second).get_value_pair();
			if (pair_buf.second) {
				av(pair_buf.first);
				valid_flag = true;
			}
		}
		return std::pair<vel2_type, bool>(av.value(),valid_flag);
	}

public:

	Autocorrelation_Box(size_t size) : map_autocorr{}, m_auto_size{size},
			last_value{} {}

	~Autocorrelation_Box() = default;

	void operator ()(Kugel<DIM>& k) {
		auto iter = map_autocorr.find(&k);
		if (iter == map_autocorr.end())
			iter = (map_autocorr.insert(
					std::pair<Kugel<DIM>*, autoT>(&k, autoT{m_auto_size})) ).first;
		(iter->second).add(k.velocity());
	}

	double value() { return double( get_value_pair().first ); }

	// Zeilenweise Ausgabe
	bool print_single(std::ostream& os) {
		auto val_pair = get_value_pair();
		if (val_pair.second) last_value = val_pair.first;

		os << (double) last_value << '\t';
		return val_pair.second;
	}

	void print_reset() {
		for (auto& el : map_autocorr) (el.second).reset_iterator();
	}

	std::ostream& print_result(std::ostream& os) {
		print_reset();
		while ( print_single(os) ) os << '\n';
		print_reset();
		return os << '\n';
	}
};

template<unsigned DIM>
std::ostream& operator <<(std::ostream& os, Autocorrelation_Box<DIM>& acorr) {
	return acorr.print_result(os);
}

#endif /* SRC_SONSTIGES_AUTOCORRELATION_BOX_HPP_ */
