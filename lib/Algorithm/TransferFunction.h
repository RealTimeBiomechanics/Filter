#ifndef TransferFunction_h
#define TransferFunction_h
#include <array>
#include <iostream>

template<size_t M, size_t N>
class TransferFunction {

public:
	TransferFunction(const std::array<double, M>& numerator, const std::array<double, N>& denominator)
		: b_(numerator),a_(denominator), count_(0) {
		y_.fill(.0); x_.fill(.0);
	}
	
	void resetState();
	double filter(double value);
	template<size_t A, size_t B>
	friend std::ostream& operator<< (std::ostream& os, const TransferFunction<A, B>& tf);
private:
	double directCoefficientsProduct() const;
	double feedbackCoefficientsProduct() const;
	void pushInput(double valueX);
	void updateOutputState(double valueY);
	std::array<double, M> b_, x_;
	std::array<double, N> a_, y_;
	size_t count_;
};

#endif


template<size_t M, size_t N>
double TransferFunction<M, N>::filter(double value) {

	pushInput(value);
	double result{ directCoefficientsProduct() + feedbackCoefficientsProduct() };
	updateOutputState(result);
	return result;
}


template<size_t M, size_t N>
double TransferFunction<M, N>::directCoefficientsProduct() const {

	double result{ 0 };
	for (unsigned k{ 0 }; k < M; ++k) 
		result += x_.at((M - k + count_) % M)*b_.at(k);
	return result;
}


template<size_t M, size_t N>
double TransferFunction<M, N>::feedbackCoefficientsProduct() const {

	double result{ 0 };
	for (unsigned k{ 1 }; k < N; ++k) 
		result += y_.at(( N - k + count_) % N)*a_.at(k);
	return -result;
}


template<size_t M, size_t N>
void TransferFunction<M, N>::pushInput(double valueX) {

	++count_;
	x_.at(count_ % M) = valueX;
	y_.at(count_ % N) = 0;
}


template<size_t M, size_t N>
void TransferFunction<M, N>::updateOutputState(double valueY) {

	y_.at(count_ % N) = valueY;
}


template<size_t M, size_t N>
void TransferFunction<M, N>::resetState() {

	x_.fill(.0);
	y_.fill(.0);
	count_ = 0;
}


template<size_t M, size_t N>
std::ostream & operator<< (std::ostream& os, const TransferFunction<M, N>& tf) {

	os << "Numerator" << std::endl;
	for (auto v : tf.b_)
		os << v << " ";
	os << std::endl;

	os << "Denominator" << std::endl;
	for (auto v : tf.a_)
		os << v << " ";
	os << std::endl;

	return os;
}