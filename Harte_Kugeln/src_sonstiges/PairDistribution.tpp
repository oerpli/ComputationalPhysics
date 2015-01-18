template<unsigned DIM>
inline PairDistribution<DIM>::PairDistribution(double width, MatVec<lengthT, DIM> length, double rho, unsigned N) : distribution(width, rho, N), box_length(length) {}

template<unsigned DIM>
inline void PairDistribution<DIM>::operator ()(const Kugel<DIM>& k1,
		const Kugel<DIM>& k2) {
	auto distance_vec = k2.position() - k1.position();
	distance_vec -= floor(distance_vec/box_length) % box_length;
	auto distance = distance_vec.norm();
	distribution(double(distance));
}

template<unsigned DIM>
inline std::ostream& PairDistribution<DIM>::print_result(std::ostream& os) {
	bool out {};
  	do {
	  	out = distribution.output(os);
	  	os << '\n';
  	} while(out);
  	distribution.output_reset();
	return os;
}

template<unsigned DIM>
inline double PairDistribution<DIM>::value() {
	return (double) (distribution.get_count());
}
