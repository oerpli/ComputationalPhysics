
template<unsigned DIM>
inline CollisionPair<DIM>::CollisionPair(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2) :
		p_kugel1 { &kugel1 }, p_kugel2 { &kugel2 }, dtime { 1E9 * s}, collision { } { //TODO dirty dtimes
}

template<unsigned DIM>
inline CollisionPair<DIM>::CollisionPair(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2,
		timeT dtime, bool collision) :
		p_kugel1 { &kugel1 }, p_kugel2 { &kugel2 }, dtime { dtime }, collision {
				collision } { }

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
inline void CollisionPair<DIM>::set_collision(Kugel<DIM>& first, Kugel<DIM>& other, const timeT& dt, bool b) {
	p_kugel1 = &first; 
	p_kugel2 = &other; 
	dtime = dt;
	collision = b;
}

template<unsigned DIM>
inline void CollisionPair<DIM>::set_collision(Kugel<DIM>& other, const timeT& dt, bool b) {
	p_kugel2 = &other; 
	dtime = dt;
	collision = b;
}

template<unsigned DIM>
inline void CollisionPair<DIM>::set_collision(const timeT& dt, bool b) {
	dtime = dt;
	collision = b;
}

template<unsigned DIM>
inline void CollisionPair<DIM>::fast_forward(const timeT& dt) {
	dtime -= dt;
}

template<unsigned DIM>
inline bool CollisionPair<DIM>::operator <(const CollisionPair<DIM>& other) const {
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
