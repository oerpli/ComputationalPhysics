template<unsigned DIM>
inline PairDistribution<DIM>::PairDistribution(double width) : distribution(width) {}

template<unsigned DIM>
inline void PairDistribution<DIM>::operator ()(const Kugel<DIM>& k1,
		const Kugel<DIM>& k2) {
	auto distance_vec = k2.position() - k1.position();
	auto distance = distance_vec.norm() / (k2.radius() * 2);
	distribution(distance);
}

template<unsigned DIM>
inline std::ostream& PairDistribution<DIM>::print_result(std::ostream& os) {
	distribution.output(os);
	return os;
}

template<unsigned DIM>
inline double PairDistribution<DIM>::value() {
	return (double) (distribution.get_count());
}
