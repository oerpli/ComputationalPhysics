#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "MatVec.h"

void empty_double_initialisation() {
	MatVec<double, 3> vec;
	bool same{true};

	for (auto& el : vec)
		same &= el == 0;
	ASSERTM("somewhere not the same", same);
}

void test_norm2() {
	MatVec<double, 3> vec{-1,2,3};
	ASSERTM("", vec.norm2() == 14);
}

void test_norm() {
	MatVec<double, 2> vec{4,-3};
	ASSERTM("", vec.norm() == 5);
}

void scalar_product() {
	MatVec<double, 3> vec1{1,2,3};
	MatVec<double, 3> vec2{-1,-3,2};

	ASSERTM("",vec1*vec2 == -1);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(empty_double_initialisation));
	s.push_back(CUTE(scalar_product));
	s.push_back(CUTE(test_norm2));
	s.push_back(CUTE(test_norm));
	//TODO add your test here
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



