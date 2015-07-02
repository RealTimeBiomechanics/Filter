#ifndef StateSpaceFilter_h
#define StateSpaceFilter_h
#include <array>
#include <iostream>
#include <vector>
#include <complex>

namespace vosl { namespace Filter {

template<typename T = double>
class StateSpaceFilter {

public:
    typedef std::complex<T> Complex;
    StateSpaceFilter();
    void resetState();
    T filter(T value, double time, double f0);
    T getFilteredValue() {
        return lastValue;
    };
    T getFilteredFirstDerivative()
    {
        return lastFirstDerivative;
    };
    T getFilteredSecondDerivative()
    {
        return lastSecondDerivative;
    };
    template<typename U>
    friend std::ostream& operator<< (std::ostream& os, const StateSpaceFilter<U>& tf);
private:
    double lastTime;
    T lastValue;
    T lastFirstDerivative;
    T lastSecondDerivative;
};

}} // namespace

#include "StateSpaceFilter.cpp"


#endif
