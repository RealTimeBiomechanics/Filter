#ifndef Filter_h
#define Filter_h
#include <array>
#include <iostream>
#include <vector>
#include "TransferFunction.h"
#include <complex>

template<typename T = std::complex<double>>
class Filter {

public:
	typedef typename T::value_type ValueType;

	Filter(const TransferFunction<T>& tf);
	void resetState();
	ValueType filter(ValueType value);
	std::vector<ValueType> pass(const std::vector<ValueType>& values);
	template<typename U>
	friend std::ostream& operator<< (std::ostream& os, const Filter<U>& tf);
private:
	T directCoefficientsProduct() const;
	T feedbackCoefficientsProduct() const;
	void pushInput(ValueType valueX);
	void updateOutputState(T valueY);
	TransferFunction<T> tf_;
	std::vector<T>  x_;
	std::vector<T>  y_; 
	size_t count_;
	size_t n_, m_;
};

#include "Filter.cpp"


#endif
