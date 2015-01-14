template<unsigned DIM>
inline CollisionPair<DIM>::CollisionPair(Kugel<DIM>& kugel1, Kugel<DIM>& kugel2,
		timeT dtime, bool collision) :
		p_kugel1 { &kugel1 }, p_kugel2 { &kugel2 }, dtime { dtime }, collision {
				collision } { }

template<unsigned DIM>
inline CollisionPair<DIM>::CollisionPair(Kugel<DIM>& k) :
		p_kugel1{&k}, p_kugel2{k.collision_partner()},
		dtime{k.collision_time()}, collision{k.collision_bool()} { }

template<unsigned DIM>
CollisionPair<DIM>& CollisionPair<DIM>::operator =(Kugel<DIM>& k) {
	return this->operator=( CollisionPair<DIM>{k} );
}

template<unsigned DIM>
template<class OtherCollisionPair>
CollisionPair<DIM>& CollisionPair<DIM>::operator <=(
		OtherCollisionPair&& other) {
	if (other < *this)
		return this->operator =(std::forward<OtherCollisionPair>(other));

	return *this;
}

template<unsigned DIM>
CollisionPair<DIM>& CollisionPair<DIM>::operator <=(Kugel<DIM>& k) {
	if ( k.collision_time() < dtime ) return operator=(k);
	return *this;
}

template<unsigned DIM>
bool CollisionPair<DIM>::operator ==(const CollisionPair<DIM> other) {
	bool result { this->p_kugel1 == other.p_kugel1 };
	if (!result)
		return result;

	result &= this->p_kugel2 == other.p_kugel2;
	if (!result)
		return result;

	result &= this->dtime == other.dtime;
	if (!result)
		return result;

	result &= this->collision == other.collision;
	return result;
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
inline void CollisionPair<DIM>::set_collision(Kugel<DIM>& first, Kugel<DIM>& other, const timeT& dt, bool b) {
	p_kugel1 = &first; 
	p_kugel2 = &other; 
	dtime = dt;
	collision = b;
}

template<unsigned DIM>
inline void CollisionPair<DIM>::fast_forward(const timeT& dt) {
	dtime -= dt;
}

template<unsigned DIM>
inline Kugel<DIM>& CollisionPair<DIM>::kugel1() {return *p_kugel1;}

template<unsigned DIM>
inline const Kugel<DIM>& CollisionPair<DIM>::kugel1() const {return *p_kugel1;}

template<unsigned DIM>
inline Kugel<DIM>& CollisionPair<DIM>::kugel2() {return *p_kugel2;}

template<unsigned DIM>
inline const Kugel<DIM>& CollisionPair<DIM>::kugel2() const {return *p_kugel2;}

template<unsigned DIM>
inline timeT CollisionPair<DIM>::collision_time() const {return dtime;}

template<unsigned DIM>
inline CollisionPair<DIM>::operator bool() const { return collision; }

//non class functions
template<unsigned DIM>
CollisionPair<DIM> set_collision(CollisionPair<DIM> cp, Kugel<DIM>& k) {
	if ( &k == &cp.kugel1() ) k.set_collision(cp.kugel2(), cp.collision_time(), (bool)cp);
	else if ( &k == &cp.kugel2() ) k.set_collision(cp.kugel1(), cp.collision_time(), (bool)cp);
	return cp;
}

template<unsigned DIM>
CollisionPair<DIM> set_collision(CollisionPair<DIM> cp, Kugel<DIM>& k1, Kugel<DIM>& k2) {
	set_collision(cp,k1);
	set_collision(cp,k2);
	return cp;
}

template<unsigned DIM>
CollisionPair<DIM> set_collision_if(CollisionPair<DIM> cp, Kugel<DIM>& k) {
	if (cp.collision_time() < k.collision_time()) set_collision(cp,k);
	return cp;
}

template<unsigned DIM>
CollisionPair<DIM> set_collision_if(CollisionPair<DIM> cp, Kugel<DIM>& k1, Kugel<DIM>& k2) {
	set_collision_if(cp,k1);
	set_collision_if(cp,k2);
	return cp;
}
