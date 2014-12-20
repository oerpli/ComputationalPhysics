#include "cute.h"
#include "test_MatVec.h"

#include "MatVec.h"

void empty_double_initialisation() {
	MatVec<double, 3> vec { };
	bool same{true};

	for (auto& el : vec)
		same &= el == 0;
	ASSERTM("somewhere not the same", same);
}

void incomplete_initialisation() {
	MatVec<double, 3> vec1 {1, 2};
	MatVec<double, 3> vec2 {1, 2, 0};

	ASSERTM("", vec1 == vec2);
}

void vektor_addition() {
	MatVec<double, 3> vec1{1,2,3};
	MatVec<double, 3> vec2{-1,-3,2};
	MatVec<double, 3> res{0,-1,5};

	ASSERTM("", vec1 + vec2 == res);
}

void vektor_subtraktion() {
	MatVec<double, 3> vec1{1,2,3};
	MatVec<double, 3> vec2{-1,-3,2};
	MatVec<double, 3> res{2,5,1};

	ASSERTM("", vec1 - vec2 == res);
}

void vektorElemente_SkalarAddition() {
	MatVec<double, 3> vec{-1,-3,2};
	MatVec<double, 3> res{1,-1,4};
	double s = 2;

	ASSERTM("", vec + s == res);
}

void vektorElemente_SkalarSubtraktion() {
	MatVec<double, 3> vec{1,-3,2};
	MatVec<double, 3> res{-1,-5,0};
	double s = 2;

	ASSERTM("", vec - s == res);
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

void multiplikation_skalar() {
	MatVec<double, 3> vec{1,-2,3};
	MatVec<double, 3> res{-2,4,-6};
	double skalar{-2};

	ASSERTM("", vec * skalar == res);
}

void division_skalar() {
	MatVec<double, 3> vec{-2,4,-6};
	MatVec<double, 3> res{1,-2,3};
	double skalar{-2};

	ASSERTM("", vec / skalar == res);
}

void make_negative() {
	MatVec<double, 3> vec{-2,4,-6};
	MatVec<double, 3> res{2,-4,6};

	ASSERTM("", -vec == res);
}


cute::suite make_suite_MatVec(){
	cute::suite s;
	s.push_back(CUTE(empty_double_initialisation));
	s.push_back(CUTE(scalar_product));
	s.push_back(CUTE(test_norm2));
	s.push_back(CUTE(test_norm));
	s.push_back(CUTE(multiplikation_skalar));
	s.push_back(CUTE(division_skalar));
	s.push_back(CUTE(make_negative));
	s.push_back(CUTE(vektor_addition));
	s.push_back(CUTE(vektor_subtraktion));
	s.push_back(CUTE(vektorElemente_SkalarAddition));
	s.push_back(CUTE(vektorElemente_SkalarSubtraktion));
	s.push_back(CUTE(incomplete_initialisation));
	return s;
}


