#ifndef TransferFunction_h
#define TransferFunction_h

#include "Polynomial.h"
#include <array>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>

template<typename T = double >
class TransferFunction {

public:
	typedef std::complex<T> Complex;
	TransferFunction(const Polynomial<T>& numerator, const Polynomial<T>& denominator) :
		numerator_(numerator), denominator_(denominator), samplingFrequency_(0.){
		normalize();
	}

	TransferFunction(const Polynomial<T>& numerator, const Polynomial<T>& denominator, double samplingFrequency) :
		numerator_(numerator), denominator_(denominator), samplingFrequency_(samplingFrequency) {
		normalize();
	}

	TransferFunction operator* (const TransferFunction<T>& tf) const;
	Complex a(unsigned i) const { return denominator_.getCoefficient(i); }
	Complex b(unsigned i) const { return numerator_.getCoefficient(i); }
	double getGainAt(double w) const;
	double getPhaseAt(double w) const;
	void getBode(std::vector<double>& xValues, std::vector<double>& gain, std::vector<double>& phase) const;
	double getSamplingFrequency() const { return samplingFrequency_; }
	void setSamplingFrequency(double samplingFrequency) { samplingFrequency_ = samplingFrequency; }

	size_t getNumeratorSize() { return numerator_.getSize(); }
	size_t getDenominatorSize() { return denominator_.getSize(); }

	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const TransferFunction<U>& tf);

private:
	Complex getResponseAt(double w) const;
	void normalize();
	double samplingFrequency_;
	Polynomial<T> numerator_, denominator_;

};


template<typename T>
void  TransferFunction<T>::normalize() {

	Complex const normalFactor(a(0));
	numerator_.divideByScalar(normalFactor);
	denominator_.divideByScalar(normalFactor);

}


template<typename T>
TransferFunction<T>  TransferFunction<T>::operator* (const TransferFunction<T>& tf) const {

	return TransferFunction<T>(numerator_*tf.numerator_, denominator_*tf.denominator_);
}

template<typename T>
typename TransferFunction<T>::Complex TransferFunction<T>::getResponseAt(double w) const {

	return numerator_.solveFor(std::exp(Complex(0, w))) / denominator_.solveFor(std::exp(Complex(0, w)));

}


template<typename T>
double TransferFunction<T>::getGainAt(double w) const {

	return 20*log10(std::abs(getResponseAt(w)));
}


template<typename T>
double TransferFunction<T>::getPhaseAt(double w) const {

	return -std::arg<T>(getResponseAt(w));
}

template<typename T>
void TransferFunction<T>::getBode(std::vector<double>& xValues, std::vector<double>& gain, std::vector<double>& phase) const {

	xValues.clear(); 
	gain.clear(); 
	phase.clear();

	for (unsigned i{ 1 }; i < static_cast<unsigned>(ceil(samplingFrequency_/2.)); ++i) {
		double w{ 2 * M_PI / samplingFrequency_ * i};
		xValues.push_back(i);
		gain.push_back(getGainAt(w));
		phase.push_back(getPhaseAt(w));
	}
	
}



template<typename U>
std::ostream& operator<<(std::ostream& os, const TransferFunction<U>& tf) {

	os << "Num: " << tf.numerator_ << std::endl;
	os << "Den: " << tf.denominator_ << std::endl;
	return os;

}

#endif