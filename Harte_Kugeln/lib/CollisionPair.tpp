
template<unsigned DIM>
inline CollisionPair<DIM>::CollisionPair(MetaKugel<DIM>& kugel1, MetaKugel<DIM>& kugel2) :
		p_kugel1 { &kugel1 }, p_kugel2 { &kugel2 }, dtime { }, collision { } {
}

template<unsigned DIM>
inline CollisionPair<DIM>::CollisionPair(MetaKugel<DIM>& kugel1, MetaKugel<DIM>& kugel2,
		time_type dtime, bool collision) :
		p_kugel1 { &kugel1 }, p_kugel2 { &kugel2 }, dtime { dtime }, collision {
				collision } {
}

template<unsigned DIM>
inline CollisionPair<DIM>& CollisionPair<DIM>::operator =(
		CollisionPair<DIM> other) {
	swap(*this, other);
	return *this;
}

template<unsigned DIM>
inline CollisionPair<DIM>& CollisionPair<DIM>::operator <=(
		const CollisionPair<DIM>& other) {
	if (other < *this)
		return operator =(other);

	return *this;
}

template<unsigned DIM>
inline void CollisionPair<DIM>::set_collision(const time_type& dt, bool b) {
	dtime = dt;
	collision = b;
}

template<unsigned DIM>
inline bool CollisionPair<DIM>::operator <(const CollisionPair<DIM>& other) const {
	if (collision != other.collision)
		return !other.collision;

	return dtime < other.dtime;
}

template<unsigned DIM>
inline bool CollisionPair<DIM>::operator >(const CollisionPair<DIM>& other) const {
	return other < *this;
}

template<unsigned DIM>
inline bool CollisionPair<DIM>::equal(const CollisionPair<DIM>& other) const {
	return (collision == other.collision && dtime == other.dtime
			&& p_kugel1 == other.p_kugel1 && p_kugel2 == other.p_kugel2);
}
