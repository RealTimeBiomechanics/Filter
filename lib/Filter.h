#ifndef Filter_h
#define Filter_h
#include <iostream>

template <typename Algorithm>
class Filter {

public:	
	Filter(Algorithm algorithm) : algorithm_(algorithm) {} 
	double filt(double value) { return algorithm_.filter(value); }
	void resetState() { algorithm_.resetState(); }
	
	template <typename T>
	friend std::ostream& operator<< (std::ostream& os, const Filter<T>& filter);
private:
	Algorithm algorithm_;

};


template <typename Algorithm>
std::ostream& operator<< (std::ostream& os, const Filter<Algorithm>& filter) {

	os << "Filter" << std::endl;
	os << filter.algorithm_ << std::endl;
	return os;
}

#endif