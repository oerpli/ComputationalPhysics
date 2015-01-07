#ifndef FUNCVEC_H_
#define FUNCVEC_H_

#include <utility>
#include <vector>
#include <memory>

#include "Auswert.h"

#include <ostream>

template<class ... Args>
class AuswertVec{
private:
public:
	std::vector<Auswert<Args ...>*> vec_func;
	AuswertVec() : vec_func{} {}
	template<class F>
	AuswertVec(F&& f) : vec_func{std::forward<F>(f)} {}

	~AuswertVec() {
		for (auto func : vec_func) delete func;
	}

	template<class F>
	void push_back(F&& f) {
		vec_func.push_back(std::forward<F>(f));
	}

	void operator() (Args ... args) {
std::cout << "FuncVec.operator()" << 	'\n';
		for (auto func : vec_func) (*func)(args...);
	}

	std::ostream& print_result(std::ostream& os){
		for (auto func : vec_func) func->print_result(os);
		return os;
	}
};

#endif //FUNCVEC_H_
