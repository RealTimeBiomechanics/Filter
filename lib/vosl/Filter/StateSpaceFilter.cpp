#include <vector>
#include <iostream>
#include <limits>

inline double pi() { return std::atan(1) * 4; } //ndElena: I wanted to mark it as constexpr, but VS2013 does not support it

namespace vosl { namespace Filter {

template<typename T>
StateSpaceFilter<T>::StateSpaceFilter() :
lastTime(std::numeric_limits<double>::infinity()),
lastValue(0.0),
lastFirstDerivative(0.0),
lastSecondDerivative(0.0)
{ }


template<typename T>
T StateSpaceFilter<T>::filter(T value, double time, double f0) {

    if (time < lastTime)
    {
        lastValue = value;
        lastFirstDerivative = 0.0;
        lastSecondDerivative = 0.0;
    }
    else
    {
        double h = time - lastTime;
        double a = (2 * pi() * f0) * (2 * pi() * f0);
        double b = sqrt(2) * 2 * pi()* f0;
        double denom = 4 + 2 * h * b + h * h * a;
        double A = (4 + 2 * h*b - h * h * a) / denom;
        double B = 4 * h / denom;
        double C = -4 * h*a / denom;
        double D = (4 - 2 * h * b - h * h * a) / denom;
        double E = 2 * h * h * a / denom;
        double F = 4 * h*a / denom;
        double y = A*lastValue + B*lastFirstDerivative + E*(value + lastValue) / 2;
        double yd = C*lastValue + D*lastFirstDerivative + F*(value + lastValue) / 2;
        lastSecondDerivative = (yd - lastFirstDerivative) / h;

        lastValue = y;
        lastFirstDerivative = yd;
    }
    lastTime = time;
    return lastValue;
}

template<typename T>
void StateSpaceFilter<T>::resetState() {
    lastTime = std::numeric_limits<double>::infinity();
    lastValue = 0.0;
    lastFirstDerivative = 0.0;
    lastSecondDerivative = 0.0;
}




template<typename T>
std::ostream & operator<< (std::ostream& os, const StateSpaceFilter<T>& filter) {
    os << "Current time : " << lastTime << std::endl;
    os << "Current value : " << lasValue << std::endl;
    os << "Current first derivative : " << lastFirstDerivative << std::endl;
    os << "Current second derivative : " << lastSecondDerivative << std::endl;

    return os;

}

}} // namespace
