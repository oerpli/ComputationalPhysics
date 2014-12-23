
template<unsigned DIM>
Kugel<DIM>::Kugel():
		MetaKugel<DIM>{}, m_cp { *this, *this } {
}

template<unsigned DIM>
Kugel<DIM>::Kugel(const Kugel& other) :
		MetaKugel<DIM> { other }, m_cp { other.m_cp } {
}

template<unsigned DIM>
Kugel<DIM>::Kugel(mass_type mass,	length_type d):
		MetaKugel<DIM> { mass, d }, m_cp { *this, *this } {
}
template <unsigned DIM>
bool Kugel<DIM>::operator ==(const Kugel<DIM>& other) const {
	return MetaKugel<DIM>::operator ==(other) && m_cp == other.m_cp;
}

template<unsigned DIM>
auto Kugel<DIM>::collision_time() const -> decltype(m_cp.collision_time()) {
	return m_cp.collision_time();
}

template<unsigned DIM>
void Kugel<DIM>::fast_forward(const time_type& dt) {
	MetaKugel<DIM>::fast_forward(dt);
	m_cp.fast_forward(dt);
}

template<unsigned DIM>
auto Kugel<DIM>::collision_pair() const -> decltype(m_cp) {
	return m_cp;
}

template<unsigned DIM>
void Kugel<DIM>::set_collision(Kugel<DIM>& other, const time_type& dt,
		bool b) {
	m_cp.set_collision(other, dt, b);
}
