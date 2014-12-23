
template<unsigned DIM>
inline Kugel<>::Kugel():
		MetaKugel { }, m_cp { *this, *this } {
}

template<unsigned DIM>
inline Kugel<>::Kugel(const Kugel& other) :
		MetaKugel { other }, m_cp { other.m_cp } {
}

template<unsigned DIM>
inline Kugel<>::Kugel(mass_type m_mass,	length_type d):
		MetaKugel { m_mass, d }, m_cp { *this, *this } {
}
template <unsigned DIM>
inline bool Kugel<DIM>::operator ==(const MetaKugel<DIM>& other) const {
	return MetaKugel<DIM>::operator ==(other) && m_cp == other.m_cp;
}

template<unsigned DIM>
inline auto Kugel<DIM>::collision_time() -> decltype(m_cp.collision_time()) {
	return m_cp.collision_time();
}

template<unsigned DIM>
inline void Kugel<DIM>::fast_forward(const time_type& dt) {
	MetaKugel<DIM>::fast_forward(dt);
	m_cp.fast_forward(dt);
}

template<unsigned DIM>
inline auto Kugel<DIM>::collision_pair() const -> decltype(m_cp) {
	return m_cp;
}

template<unsigned DIM>
inline void Kugel<DIM>::set_collision(Kugel<DIM>& other, const time_type& dt,
		bool b) {
	m_cp.set_collision(other, dt, b);
}
