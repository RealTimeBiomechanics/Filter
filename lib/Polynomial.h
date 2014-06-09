#ifndef Polynomial_h
#define Polynomial_h
#include <vector>
#include <iostream>
#include <initializer_list>
#include <complex>

template <typename T = double>
class Polynomial {
	
public:
	typedef std::complex<T> Complex;
	Polynomial() {};
	Polynomial(const std::vector<Complex>& coefficients);
	Polynomial(const std::initializer_list<Complex>& coefficients);
	Polynomial(const std::initializer_list<T>& coefficients);
	Polynomial(size_t order);
	Complex solveFor(Complex value) const;
	unsigned getOrder() const;
	size_t getSize() const;
	Complex getCoefficient(unsigned i) const { return coefficients_.at(i); }
	void divideByScalar(Complex value);

	template<typename U>
	friend Polynomial<U> multiply(const Polynomial<U>& p1, const Polynomial<U>& p2);

	Polynomial operator* (const Polynomial<T>& p) const;

	template<typename U>
	friend Polynomial<U> add(const Polynomial<U>& p1, const Polynomial<U>& p2);

	template<typename U>
	friend std::ostream& operator<< (std::ostream& os, const Polynomial<U>& p);

private:
	std::vector<Complex> coefficients_;
	size_t order_;
	size_t size_;
};


#include "Polynomial.cpp"
#endif