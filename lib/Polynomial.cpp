#include <algorithm>
#include <vector>

template <typename T>
Polynomial<T>::Polynomial(const std::vector<T>& coefficients) :
coefficients_(coefficients), order_(coefficients.size() - 1), size_(coefficients.size()) { }


template <typename T>
Polynomial<T>::Polynomial(size_t order) :
coefficients_(order + 1, .0), size_(order + 1), order_(order) { }



template <typename T>
unsigned Polynomial<T>::getOrder() const {

	return order_;
}


template <typename T>
size_t Polynomial<T>::getSize() const {

	return size_;
}


template <typename T>
Polynomial<T> add(const Polynomial<T>& p1, const Polynomial<T>& p2) {

	Polynomial<T> result(std::max(p1.getOrder(), p2.getOrder()));
	for (unsigned i{ 0 }; i < result.getSize(); ++i) {
		if (i < p1.getSize())
			result.coefficients_.at(i) += p1.coefficients_.at(i);
		if (i < p2.getSize())
			result.coefficients_.at(i) += p2.coefficients_.at(i);
	}
	return result;
}


template <typename T>
Polynomial<T> multiply(const Polynomial<T>& p1, const Polynomial<T>& p2) {

	size_t resultOrder(p1.getOrder() + p2.getOrder());
	std::vector<T> resultCoefficients(2 * resultOrder + 1);
	std::vector<T> temp1(2 * resultOrder + 1), temp2(2 * resultOrder + 1);
	for (unsigned i{ 0 }; i < p1.getSize(); ++i)
		temp1.at(i) = p1.coefficients_.at(i);

	for (unsigned i{ 0 }; i < p2.getSize(); ++i)
		temp2.at(i) = p2.coefficients_.at(i);


	for (unsigned k{ 0 }; k < resultCoefficients.size() - 1; ++k)
	for (unsigned i{ 0 }; i <= k; ++i)
		resultCoefficients.at(k) += temp1.at(i)*temp2.at(k - i);

	auto it = std::find_if(resultCoefficients.rbegin(), resultCoefficients.rend(), [](T v){ return v != 0;	});

	Polynomial<T> result(std::vector<T>(resultCoefficients.begin(), it.base()));

	return result;


}

template <typename T>
Polynomial<T> Polynomial<T>::operator* (const Polynomial<T>& p) const {

	return multiply(*this, p);
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const Polynomial<T>& p) {

	os << "[";
	for (auto c(p.coefficients_.begin()); c != p.coefficients_.end() - 1; ++c)
		os << *c << ", ";
	os << p.coefficients_.back() << "]" << std::endl;

	return os;
}

