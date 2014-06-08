#ifndef TransferFunction_h
#define TransferFunction_h

#include "Polynomial.h"
#include <array>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <complex>

template<typename T = double >
class TransferFunction {

public:
	TransferFunction(const Polynomial<T>& numerator, const Polynomial<T>& denominator) :
		numerator_(numerator), denominator_(denominator) {
		normalize();
	}

	TransferFunction operator* (const TransferFunction<T>& tf) const;
	T a(unsigned i) const { return denominator_.getCoefficient(i); }
	T b(unsigned i) const { return numerator_.getCoefficient(i); }
	double getGainAt(double w) const {
		return std::abs(getResponseAt(w));
	}
	double getPhaseAt(double w) const {};

	size_t getNumeratorSize() { return numerator_.getSize(); }
	size_t getDenominatorSize() { return denominator_.getSize(); }

	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const TransferFunction<U>& tf);
private:
	T getResponseAt(double w) const;
	void normalize();
	Polynomial<T> numerator_, denominator_;

};


template<typename T>
void  TransferFunction<T>::normalize() {

	T const normalFactor{ a(0) };
	numerator_.divideByScalar(normalFactor);
	denominator_.divideByScalar(normalFactor);

}


template<typename T>
TransferFunction<T>  TransferFunction<T>::operator* (const TransferFunction<T>& tf) const {

	return TransferFunction<T>(numerator_*tf.numerator_, denominator_*tf.denominator_);
}

template<typename T>
T TransferFunction<T>::getResponseAt(double w) const {

	return numerator_.solveFor(std::complex<double>(0, w)) / denominator_.solveFor(std::complex<double>(0, w));

}


template<typename U>
std::ostream& operator<<(std::ostream& os, const TransferFunction<U>& tf) {

	os << "Num: " << tf.numerator_ << std::endl;
	os << "Den: " << tf.denominator_ << std::endl;
	return os;

}

#endif