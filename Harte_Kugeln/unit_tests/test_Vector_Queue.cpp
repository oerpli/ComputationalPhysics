#include "cute.h"
#include "test_Vector_Queue.h"

#include <iostream>
#include "Vector_Queue.hpp"

const std::vector<int> ivec{1,2,3,4,5};

void make_empty_int_capacity_10() {
	size_t size{10};
	Vector_Queue<int> vq{size};

	ASSERTM("", vq.capacity() == size && vq.size() == 0);
}

void make_queue_from_vec() {
	Vector_Queue<int> vq{ivec};

	ASSERTM("", vq.size() == ivec.size() );
}

void compare_queue_with_vec_false_size() {
	std::vector<int> v1{1,2,4,3}, v2{1,2,4};
	Vector_Queue<int> vq{v1};

	ASSERTM("", !( vq == v2 ) );
}

void compare_queue_with_vec_false_element() {
	std::vector<int> v1{1,2,4,3}, v2{1,2,4,5};
	Vector_Queue<int> vq{v1};

	ASSERTM("", !( vq == v2 ) );
}

void compare_queue_with_vec_true() {
	Vector_Queue<int> vq{ivec};

	ASSERTM("", vq == ivec );
}

void test_indexing_with_vector() {
	Vector_Queue<int> vq{ivec};
	bool flag{true};

	for(size_t i{}; i<ivec.size(); ++i)
		flag &= ivec[i] == vq[i];

	ASSERTM("", flag);
}

void test_iterator_with_vector() {
	Vector_Queue<int> vq{ivec};
	bool flag{true};

	auto iter_vec = ivec.begin();
	auto iter_vq  = vq.begin();

	for( ; iter_vec != ivec.end() && iter_vq != vq.end(); ++iter_vec, ++iter_vq)
		flag &= *iter_vec == *iter_vq;

	ASSERTM("", flag);
}

void queue_add_one_element() {
	Vector_Queue<int> vq{2};
	int el{12};
	vq.add(el);

	ASSERTM("", vq.size() == 1 && vq[0] == el);
}

void queue_add_too_many_elements() {
	std::vector<int> v_in{4,2,4,2}, v_res{1,3,2,5};
	Vector_Queue<int> vq{v_res.size()};
	for(auto iter = v_res.begin(); iter != v_res.end(); ++iter)
		v_in.push_back(*iter);

	for(const auto& el : v_in) vq.add(el);
	ASSERTM("", vq == v_res);
}

cute::suite make_suite_Vector_Queue(){
	cute::suite s;
	s.push_back(CUTE(make_empty_int_capacity_10));
	s.push_back(CUTE(make_queue_from_vec));
	s.push_back(CUTE(compare_queue_with_vec_false_size));
	s.push_back(CUTE(compare_queue_with_vec_false_element));
	s.push_back(CUTE(compare_queue_with_vec_true));
	s.push_back(CUTE(test_indexing_with_vector));
	s.push_back(CUTE(test_iterator_with_vector));
	s.push_back(CUTE(queue_add_one_element));
	s.push_back(CUTE(queue_add_too_many_elements));
	return s;
}
