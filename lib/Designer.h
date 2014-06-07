#ifndef Designer_h
#define Designer_h

#define _USE_MATH_DEFINES
#include <math.h>

#include "TransferFunction.h"

namespace Designer {

	enum class Type {LowPass, HighPass, BandPass};

	// The cutoff frequency
	// wn must be 0.0 < wn < 1.0, with 1.0 corresponding to
	// half the sample rate.
	template <typename T>
	TransferFunction<T> butter(unsigned order, double fc, double fs, Type t) {

		double correction = 1. / pow(pow(2, 1./static_cast<double>(order)) - 1, 1./4.);
		double fc2 = fc * correction;
		double wc = tan(M_PI*fc2 / fs);

	}

};







#endif