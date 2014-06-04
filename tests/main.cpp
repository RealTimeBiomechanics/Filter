#include "Filter.h"
#include "Algorithm/TransferFunction.h"
#include <array>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

int main() {

	//coefficients from MATLAB 
	// [numerator, denominator] = butter(2, .006, 'low')
	std::array<double, 3> numerator{ { 8.76555487540065,	17.5311097508013,	8.76555487540065 } };
	for (auto &val : numerator) val *= 1e-5;
	std::array<double, 3> denominator{ { 1, -1.97334424978130,	0.973694871976315} };

	using TF = TransferFunction<3, 3>;
	TF tf(numerator, denominator);
	Filter<TF> filter(tf);
	std::cout << filter;

	//step response
	std::vector<double> zeroes(10, 0.0);
	std::vector<double> ones(1000, 1.0);
	std::vector<double> step(zeroes);
	step.insert(step.end(), ones.begin(), ones.end());

	std::ofstream oF("output.csv");
	for (double val : step)
		oF << val << "," << filter.filt(val) << std::endl;

	oF.close();
	std::exit(EXIT_SUCCESS);
}