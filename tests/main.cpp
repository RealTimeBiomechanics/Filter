#include "Filter.h"
#include "TransferFunction.h"
#include "Designer.h"
#include <array>
#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "Polynomial.h"
#include <complex>


int main() {

	//coefficients from MATLAB 
	// [numerator, denominator] = butter(2, .006, 'low')

	Polynomial<> numerator{ 8.76555487540065e-5, 17.5311097508013e-5, 8.76555487540065e-5 };
	Polynomial<> denominator{ 1, -1.97334424978130, 0.973694871976315 };

	TransferFunction<> tf(numerator, denominator), tfTest({ 1 }, { 1, 2, 3 });


	Filter<> filter(tf), filter2(tf*tf);
	
	
	//step response
	std::vector<double> zeroes(1000, 0.0);
	std::vector<double> ones(1000, 1.0);
	std::vector<double> step(zeroes);
	step.insert(step.end(), ones.begin(), ones.end());

	std::cout << filter2;
	std::ofstream oF("output.csv");
	for (double val : step)
		oF << val << "," << filter.filter(val) << ", " << filter2.filter(val) << std::endl;
	oF.close();


	//test filtfilt
	

	
	//test filtfilt
	vector<double> firstPass(filter.pass(step));
	std::reverse(firstPass.begin(), firstPass.end());
	vector<double> secondPass(filter.pass(firstPass));
	std::reverse(secondPass.begin(), secondPass.end());

	std::reverse(firstPass.begin(), firstPass.end());

	std::ofstream oF2("filtfilt.csv");
	for (unsigned i{ 0 }; i < step.size(); ++i)
		oF2 << step.at(i) << "," << firstPass.at(i) << "," << secondPass.at(i) << std::endl;
	oF2.close();


	
	
	//test linear phase fir filter 
	std::vector<std::complex<double>> firB( { 
		 0.00127199776427371,
		 0.00175973248875467,
		-0.000474050123699974,
		-0.00507655778150986,
		-0.00730622779100510,
		-0.00139834985893385,
		 0.0118182305510141,
		 0.0208600394665444,
		 0.0108509633977398,
		-0.0201948738097724,
		-0.0503421398292688,
		-0.0426075899832280,
		 0.0273002961309331,
		 0.144919701151270,
		 0.257048286517307,
		 0.303233271924363,
		 0.257048286517307,
		 0.144919701151270,
		 0.0273002961309331,
		-0.0426075899832280,
		-0.0503421398292688,
		-0.0201948738097724,
		 0.0108509633977398,
		 0.0208600394665444,
		 0.0118182305510141,
		-0.00139834985893385,
		-0.00730622779100510,
		-0.00507655778150986,
		-0.000474050123699974,
		 0.00175973248875467,
		 0.00127199776427371
	} );

	Polynomial<> n(firB), d{ 1 };

	TransferFunction<> tfFir(n, d);
	Filter<> firFilter(tfFir);
	vector<double> resultFir(firFilter.pass(step));

	std::ofstream oF3("comparison.csv");
	for (unsigned i{ 0 }; i < step.size(); ++i)
		oF3 << step.at(i) << "," << firstPass.at(i) << "," << secondPass.at(i) << ", " << resultFir.at(i) << std::endl;
	oF3.close();


	/*
	std::vector<double> coeff({ 1, 2, 3, 4, 5});
	Polynomial<double> p(coeff);
	std::cout << p;
	//std::cout << add(p, Polynomial<double>(std::vector<double>{ 1, 2, 3, 4 }));
	std::cout << multiply(p, p);
	std::cout << p*p;
	*/
	std::exit(EXIT_SUCCESS);
}