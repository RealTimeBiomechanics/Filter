#include <vector>
#include <iostream>
#include <complex>

template<typename T>
Filter<T>::Filter(const TransferFunction<T>& tf) :
tf_(tf),
count_(0),
y_(tf_.denominator_.getSize(), .0),
x_(tf_.numerator_.getSize(), .0),
n_(tf_.denominator_.getSize()),
m_(tf_.numerator_.getSize())  { }

template<typename T>
typename Filter<T>::ValueType Filter<T>::filter(ValueType value) {

	pushInput(value);
	T result{ directCoefficientsProduct() + feedbackCoefficientsProduct() };
	updateOutputState(result);
	return result.real();
}


template<typename T>
T Filter<T>::directCoefficientsProduct() const {

	T result{ 0 };
	for (unsigned k{ 0 }; k < m_; ++k)
		result += x_.at((m_ - k + count_) % m_)*tf_.b(k);
	return result;
}


template<typename T>
T Filter<T>::feedbackCoefficientsProduct() const {

	T result{ 0 };
	for (unsigned k{ 1 }; k < n_; ++k)
		result += y_.at((n_ - k + count_) % n_)*tf_.a(k);
	return -result;
}


template<typename T>
void Filter<T>::pushInput(ValueType valueX) {

	++count_;
	x_.at(count_ % m_) = valueX;
	y_.at(count_ % n_) = 0;
}


template<typename T>
void Filter<T>::updateOutputState(T valueY) {

	y_.at(count_ % n_) = valueY;
}


template<typename T>
void Filter<T>::resetState() {

	for (T& element : x_)
		element = 0;
	for (T& element : y_)
		element = 0;

	count_ = 0;
}



template<typename T>
std::vector<typename Filter<T>::ValueType> Filter<T>::pass(const std::vector<ValueType>& values) {

	resetState();
	std::vector<typename Filter<T>::ValueType>filteredValues;
	for (auto val : values)
	filteredValues.push_back(filter(val));
	return filteredValues;
}


template<typename T>
std::ostream & operator<< (std::ostream& os, const Filter<T>& filter) {

	os << "Numerator" << std::endl << filter.tf_.numerator_ << std::endl;
	os << "Denominator" << std::endl << filter.tf_.denominator_ << std::endl;

	return os;
}
