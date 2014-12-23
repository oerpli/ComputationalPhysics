template <unsigned DIM>
MetaKugel<DIM>::MetaKugel() :
		m_mass(mass_type { }), m_radius(length_type { })
		, m_ekin{}, vec_vel{}, vec_pos{} {}

template <unsigned DIM>
MetaKugel<DIM>::MetaKugel(const MetaKugel<DIM> & kugel) : m_mass{kugel.m_mass},
	m_radius{kugel.m_radius},
	m_ekin{kugel.m_ekin},
	vec_vel{kugel.vec_vel},
	vec_pos{kugel.vec_pos} {}

template <unsigned DIM>
MetaKugel<DIM>::MetaKugel(mass_type m, length_type d) :
		m_mass { m }, m_radius { d }
		, m_ekin{}, vec_vel{}, vec_pos{} {}


template <unsigned DIM>
bool MetaKugel<DIM>::operator ==(const MetaKugel<DIM>& other) const {
	bool flag{ m_ekin == other.m_ekin };
	if (! flag)
		return flag;

	flag &= vec_vel == vec_vel;
	if (! flag)
		return flag;

	flag &= vec_pos == vec_pos;
	if (! flag)
		return flag;

	flag &= ( m_mass == other.m_mass && m_radius == m_radius );

	return flag;
}

template<unsigned DIM>
void MetaKugel<DIM>::update_ekin() {
	m_ekin = m_mass * vec_vel.norm2() * 0.5;
}

template<unsigned DIM>
void MetaKugel<DIM>::velocity(MatVec<velocity_type, DIM> vec) {
	swap(vec_vel, vec);
	update_ekin();
}

template<unsigned DIM>
auto MetaKugel<DIM>::velocity() const -> decltype(vec_vel) {
	return vec_vel;
}

template<unsigned DIM>
void MetaKugel<DIM>::position(MatVec<length_type, DIM> vec) {
	swap(vec_pos, vec);
	update_ekin();
}

template<unsigned DIM>
auto MetaKugel<DIM>::position() const -> decltype(vec_pos) {
	return vec_pos;
}

template<unsigned DIM>
auto MetaKugel<DIM>::ekin() const -> decltype(m_ekin) {
	return m_ekin;
}

template <unsigned DIM>
std::ostream& MetaKugel<DIM>::print(std::ostream & os) const {
	os << "Mass: " << m_mass << '\n'; //Falls wir wieder zu langsam bei der Ausgabe sind
	os << "Diameter: " << m_radius << '\n';
	os << "Ekin: " << m_ekin << '\n';
	os << "Position: " << vec_pos << '\n';
	os << "Velocity: " << vec_vel << '\n';
	return os;
}


template<unsigned DIM>
void MetaKugel<DIM>::fast_forward(const time_type& dt) {
	vec_pos += vec_vel * dt;
}

