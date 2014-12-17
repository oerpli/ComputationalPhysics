template <unsigned DIM>
Kugel<DIM>::Kugel() :
		m_mass(mass_type { }), m_diameter(length_type { })
		, m_ekin{}, vec_vel{}, vec_pos{} {}

template <unsigned DIM>
Kugel<DIM>::Kugel(const Kugel<DIM> & kugel) : m_mass{kugel.m_mass},
	m_diameter{kugel.m_diameter},
	m_ekin{kugel.m_ekin},
	vec_vel{kugel.vec_vel},
	vec_pos{kugel.vec_pos} {}

template <unsigned DIM>
Kugel<DIM>::Kugel(mass_type m, length_type d) :
		m_mass { m }, m_diameter { d }
		, m_ekin{}, vec_vel{}, vec_pos{} {}

template<unsigned DIM>
void Kugel<DIM>::update_ekin() {
	quantity < dose_equivalent > v2sum { };
	for (auto& v : vec_vel)
		v2sum += pow < 2 > (v);
	m_ekin = 0.5 * m_mass * v2sum;
}

template<unsigned DIM>
void Kugel<DIM>::velocity(MatVec<velocity_type, DIM> vec) {
	swap(vec_vel, vec);
	update_ekin();
}

template<unsigned DIM>
auto Kugel<DIM>::velocity() const -> decltype(vec_vel) {
	return vec_vel;
}

template<unsigned DIM>
auto Kugel<DIM>::ekin() const -> decltype(m_ekin) {
	return m_ekin;
}

template <unsigned DIM>
std::ostream& Kugel<DIM>::print(std::ostream & os) const {
	os << "Mass: " << m_mass << '\n'; //Falls wir wieder zu langsam bei der Ausgabe sind
	os << "Diameter: " << m_diameter << '\n';
	os << "Ekin: " << m_ekin << '\n';
	os << "Position: " << vec_pos << '\n';
	os << "Velocity: " << vec_vel << '\n';
	return os;
}


