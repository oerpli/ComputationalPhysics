#ifndef AUSWERT_H_
#define AUSWERT_H_

#include <ostream>

template<class ... Args>
class Auswert {
public:
	virtual ~Auswert(){}
	virtual void operator() (const Args& ... args){}
	virtual double value(){return -1.0;}
	virtual std::ostream& print_result(std::ostream& os) {return os;}
};

#endif //AUSWERT_H_
