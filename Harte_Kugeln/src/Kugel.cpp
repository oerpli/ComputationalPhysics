template <unsigned DIM>
Kugel<DIM>::Kugel() : m_mass(quantity<mass>{}), m_diameter(quantity<length>{})
					, vec_pos{}, vec_vel{} {}

template <unsigned DIM>
Kugel<DIM>::Kugel(const Kugel<DIM> & kugel) : m_mass{kugel.m_mass},
	m_diameter{kugel.m_diameter},
	vec_pos{kugel.vec_pos},
	vec_vel{kugel.vec_vel} {}

template <unsigned DIM>
Kugel<DIM>::Kugel(quantity<mass> m, quantity<length> d) : m_mass{m}, m_diameter{d}
														, vec_pos{}, vec_vel{} {}

template <unsigned DIM>
std::ostream& Kugel<DIM>::print(std::ostream & os) const {
	os << "Mass: " << m_mass << '\n'; //Falls wir wieder zu langsam bei der Ausgabe sind
	os << "Diameter: " << m_diameter << '\n';
	os << "Position: " << vec_pos << '\n';
	os << "Velocity: " << vec_vel << '\n';
	return os;
}

