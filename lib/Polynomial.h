#ifndef Polynomial_h
#define Polynomial_h
#include <vector>
#include <iostream>
#include <initializer_list>
#include <complex>

template <typename T = std::complex<double>>
class Polynomial {

public:
	Polynomial() {};
	Polynomial(const std::vector<T>& coefficients);
	Polynomial(const std::initializer_list<T>& coefficients);
	Polynomial(size_t order);
	unsigned getOrder() const;
	size_t getSize() const;
	T getCoefficient(unsigned i) const { return coefficients_.at(i); }

	template<typename U>
	friend Polynomial<U> multiply(const Polynomial<U>& p1, const Polynomial<U>& p2);

	Polynomial operator* (const Polynomial<T>& p) const;

	template<typename U>
	friend Polynomial<U> add(const Polynomial<U>& p1, const Polynomial<U>& p2);

	template<typename U>
	friend std::ostream& operator<< (std::ostream& os, const Polynomial<U>& p);


private:
	std::vector<T> coefficients_;
	size_t order_;
	size_t size_;
};


#include "Polynomial.cpp"
#endif