template<unsigned DIM>
Kugel<DIM>::Kugel(massT mass,	lengthT r):
		m_mass { mass }, m_radius { r },
		m_ekin{}, vec_vel{}, vec_pos{},
		m_p_partner{}, m_t_collision{}, m_b_collision{} {}

template <unsigned DIM>
bool Kugel<DIM>::operator ==(const Kugel<DIM>& other) const {
	bool result{ m_p_partner == other.m_p_partner };
	if (! result) return result;

	result &= m_t_collision == other.m_t_collision;
	if (! result) return result;

	result &= m_b_collision == other.m_b_collision;
	if (! result) return result;

	result &= m_ekin == other.m_ekin;
	if (! result) return result;

	result &= vec_vel == vec_vel;
	if (! result) return result;

	result &= vec_pos == vec_pos;
	if (! result) return result;

	result &= ( m_mass == other.m_mass && m_radius == m_radius );

	return result;
}


template<unsigned DIM>
void Kugel<DIM>::update_ekin() {
	m_ekin = m_mass * vec_vel.norm2() * 0.5;
}

template<unsigned DIM>
void Kugel<DIM>::velocity(MatVec<velocityT, DIM> vec) {
	swap(vec_vel, vec);
	update_ekin();
}

template<unsigned DIM>
auto Kugel<DIM>::velocity() const -> decltype(vec_vel) {
	return vec_vel;
}

template<unsigned DIM>
void Kugel<DIM>::position(MatVec<lengthT, DIM> vec) {
	swap(vec_pos, vec);
	update_ekin();
}

template<unsigned DIM>
auto Kugel<DIM>::position() const -> decltype(vec_pos) {
	return vec_pos;
}

template<unsigned DIM>
auto Kugel<DIM>::ekin() const -> decltype(m_ekin) {
	return m_ekin;
}

template <unsigned DIM>
std::ostream& Kugel<DIM>::print(std::ostream & os) const {
	os << "Mass: " << m_mass << '\n'; //Falls wir wieder zu langsam bei der Ausgabe sind
	os << "Diameter: " << m_radius << '\n';
	os << "Ekin: " << m_ekin << '\n';
	os << "Position: " << vec_pos << '\n';
	os << "Velocity: " << vec_vel << '\n';
	return os;
}

template<unsigned DIM>
timeT Kugel<DIM>::collision_time() const {
	return m_t_collision;
}

template<unsigned DIM>
void Kugel<DIM>::fast_forward(const timeT& dt) {
	vec_pos += vec_vel * dt;
	m_t_collision -= dt;
}

template<unsigned DIM>
void Kugel<DIM>::set_collision(Kugel<DIM>& other, const timeT& dt,
		bool b) {
	m_p_partner = &other;
	m_t_collision = dt;
	m_b_collision = b;
}
