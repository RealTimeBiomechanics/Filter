#include <vector>
#include <iostream>


template<typename T>
Filter<T>::Filter(const TransferFunction<T>& tf) :
tf_(tf),
count_(0),
y_(tf_.getDenominatorSize(), .0),
x_(tf_.getNumeratorSize(), .0),
n_(tf_.getDenominatorSize()),
m_(tf_.getNumeratorSize())  { }

template<typename T>
T Filter<T>::filter(T value) {

	pushInput(value);
	T result{ directCoefficientsProduct() + feedbackCoefficientsProduct() };
	updateOutputState(result);
	return result;
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
void Filter<T>::pushInput(T valueX) {

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
std::vector<T> Filter<T>::pass(const std::vector<T>& values) {

	resetState();
	std::vector<T> filteredValues;
	for (auto val : values)
		filteredValues.push_back(filter(val));
	return filteredValues;
}


template<typename T>
std::ostream & operator<< (std::ostream& os, const Filter<T>& filter) {

	//os << "Numerator" << std::endl << filter.tf_ << std::endl;

	return os;
}
