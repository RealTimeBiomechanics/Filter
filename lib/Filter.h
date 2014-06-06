#ifndef Filter_h
#define Filter_h
#include <array>
#include <iostream>
#include <vector>
#include "TransferFunction.h"

template<typename T>
class Filter {

public:
	Filter(const TransferFunction<T>& tf);
	void resetState();
	T filter(T value);
	std::vector<T> pass(const std::vector<T>& values);
	template<typename U>
	friend std::ostream& operator<< (std::ostream& os, const Filter<U>& tf);
private:
	T directCoefficientsProduct() const;
	T feedbackCoefficientsProduct() const;
	void pushInput(T valueX);
	void updateOutputState(T valueY);
	TransferFunction<T> tf_;
	std::vector<T>  x_;
	std::vector<T>  y_; 
	size_t count_;
	size_t n_, m_;
};

#include "Filter.cpp"


#endif
