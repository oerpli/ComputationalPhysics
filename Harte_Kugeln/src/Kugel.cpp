template <typename LengthType, typename VelocityType, typename MassType, int DIM>
Kugel<LengthType, VelocityType, MassType, DIM>::Kugel() : mass(MassType()), diameter(LengthType()) {
	for (int i = 0; i < DIM; i++) {
		position.push_back(LengthType());
		velocity.push_back(VelocityType());
	}
}

template <typename LengthType, typename VelocityType, typename MassType, int DIM>
Kugel<LengthType, VelocityType, MassType, DIM>::Kugel(const Kugel<LengthType, VelocityType, MassType, DIM> & kugel) : mass{kugel.mass},
	diameter{kugel.diameter},
	position{kugel.position},
	velocity{kugel.velocity} {}

template <typename LengthType, typename VelocityType, typename MassType, int DIM>
Kugel<LengthType, VelocityType, MassType, DIM>::Kugel(MassType m, LengthType d) : mass(m), diameter(d) {
	for (int i = 0; i < DIM; i++) {
		position.push_back(LengthType());
		velocity.push_back(VelocityType());
	}
}

template <typename LengthType, typename VelocityType, typename MassType, int DIM>
std::ostream& Kugel<LengthType, VelocityType, MassType, DIM>::print(std::ostream & os) const {
	os << mass << " ";
	os << diameter << " ";
	os << position << " ";
	os << velocity << std::endl;
	return os;
}


