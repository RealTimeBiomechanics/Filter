#ifndef TransferFunction_h
#define TransferFunction_h

#include "Polynomial.h"
#include <array>
#include <iostream>
#include <algorithm>
#include <vector>


template<typename T>
class TransferFunction {

public:
	TransferFunction(const Polynomial<T>& numerator, const Polynomial<T>& denominator) :
		numerator_(numerator), denominator_(denominator) {}

	TransferFunction operator* (const TransferFunction<T>& tf) const;
	T a(unsigned i) const { return denominator_.getCoefficient(i); }
	T b(unsigned i) const { return numerator_.getCoefficient(i); }

	Polynomial<T> numerator_, denominator_;

};

template<typename T>
TransferFunction<T>  TransferFunction<T>::operator* (const TransferFunction<T>& tf) const {

	return TransferFunction<T>(numerator_*tf.numerator_, denominator_*tf.denominator_);
}

#endif