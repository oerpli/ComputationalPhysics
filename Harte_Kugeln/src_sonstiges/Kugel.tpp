
template<unsigned DIM>
Kugel<DIM>::Kugel():
		MetaKugel<DIM>{},
		m_p_partner{}, m_t_collision{}, m_b_collision{false} {
}

template<unsigned DIM>
Kugel<DIM>::Kugel(const Kugel& other) :
		MetaKugel<DIM> { other },
		m_p_partner{other.m_p_partner},
		m_t_collision{other.m_t_collision},
		m_b_collision{other.m_b_collision} {
}

template<unsigned DIM>
Kugel<DIM>::Kugel(massT mass,	lengthT d):
		MetaKugel<DIM> { mass, d },
		m_p_partner{}, m_t_collision{}, m_b_collision{false} {
}
template <unsigned DIM>
bool Kugel<DIM>::operator ==(const Kugel<DIM>& other) const {
	bool result{ m_p_partner == other.m_p_partner };
	result &= m_t_collision == other.m_t_collision;
	result &= m_b_collision == other.m_b_collision;
	return result && MetaKugel<DIM>::operator ==(other);
}

template<unsigned DIM>
timeT Kugel<DIM>::collision_time() const {
	return m_t_collision;
}

template<unsigned DIM>
void Kugel<DIM>::fast_forward(const timeT& dt) {
	MetaKugel<DIM>::fast_forward(dt);
	m_t_collision -= dt;
}

template<unsigned DIM>
void Kugel<DIM>::set_collision(Kugel<DIM>& other, const timeT& dt,
		bool b) {
	m_p_partner = &other;
	m_t_collision = dt;
	m_b_collision = b;
}
