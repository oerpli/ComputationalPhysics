#include <iostream>
#include <vector>

template <typename LengthType, typename VelocityType, typename MassType, int DIM>
class Kugel {
public:
	MassType mass;
	LengthType diameter;
	std::vector<LengthType> position;
	std::vector<VelocityType> velocity;
	//collision next_collision;

	Kugel();
	Kugel(const Kugel<LengthType, VelocityType, MassType, DIM> & kugel);
	Kugel(MassType m, LengthType d);

	friend void swap(Kugel<LengthType, VelocityType, MassType, DIM>& kugelA, Kugel<LengthType, VelocityType, MassType, DIM>& kugelB) {
			std::swap(kugelA.position, kugelB.position);
			std::swap(kugelA.velocity, kugelB.velocity);
			std::swap(kugelA.mass, kugelB.mass);
			std::swap(kugelA.diameter, kugelB.diameter);
	}

	std::ostream& print(std::ostream & os = std::cout) const;


};


#include "Kugel.cpp"


