#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <vector>
#include "Kugel.h"
#include "MatVec.h"

template<unsigned DIM>
class Box {
	typedef quantity<length> lengthT;
	std::vector<Kugel<DIM>> vec_kugel;
	MatVec<lengthT, DIM> vec_abmessung;

public:
	Box(unsigned size, const MatVec<lengthT, DIM>& dim)
		: vec_kugel(size), vec_abmessung{dim} {}
	Box(const MatVec<lengthT, DIM>& dim)
			: Box{0,dim} {}

	auto size() const -> decltype( vec_kugel.size() ){
		return vec_kugel.size();
	}

	auto abmessung() const -> decltype( vec_abmessung ) {
		return vec_abmessung;
	}

	void add(const Box<DIM>& other) {
		if ( vec_abmessung != other.vec_abmessung )
			return;
		vec_kugel.insert(vec_kugel.end(),
				other.vec_kugel.begin(), other.vec_kugel.end() );
	}

};


const length m = meter;
const force N = newton;
const velocity mps = meters_per_second;
typedef quantity<length> lengthT;
typedef quantity<force> forceT;
typedef quantity<velocity> velocityT;


void emptyBox() {
	MatVec<lengthT, 3> a{1*m,2*m,3*m};
	Box<3> box { a };
	ASSERTM("", box.size() == 0 );
}


void boxSize10() {
	MatVec<lengthT, 3> a{1*m,2*m,3*m};
	Box<3> box { 10, a };
	ASSERTM("", box.size() == 10 );
}

void boxAbmessung() {
	MatVec<lengthT, 3> a{1*m,2*m,3*m};
	Box<3> box {10, a};
	ASSERTM("", box.abmessung() == a);
}

void addBoxSize() {
	MatVec<lengthT, 3> a{1*m,2*m,3*m};
	unsigned s1 { 10 }, s2 { 15 };
	Box<3> box1{s1, a}, box2{s2, a};
	box1.add(box2);
	ASSERTM("", box1.size() == s1 + s2);
}
void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(emptyBox));
	s.push_back(CUTE(boxSize10));
	s.push_back(CUTE(boxAbmessung));
	s.push_back(CUTE(addBoxSize));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



