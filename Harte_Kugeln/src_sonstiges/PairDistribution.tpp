template<unsigned DIM>
inline PairDistribution<DIM>::PairDistribution(double width, double rho, unsigned N) : distribution(width, rho, N) {}

template<unsigned DIM>
inline void PairDistribution<DIM>::operator ()(const Kugel<DIM>& k1,
		const Kugel<DIM>& k2, const lengthT& dist) {
	distribution(double(dist));
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
