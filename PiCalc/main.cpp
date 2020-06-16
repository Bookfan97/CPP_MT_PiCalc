#include <iostream>
#include "PiMulti.h"
#include "PiSingle.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

int main()
{
	std::cout << "=====================================================================================" << std::endl;
	auto startTime_single = high_resolution_clock::now();
	PiSingle();
	auto stopTime_single = high_resolution_clock::now();
	duration<double> time_span_single = duration_cast<duration<double>>(stopTime_single - startTime_single);
	auto startTime_multi = high_resolution_clock::now();
	PiMulti();
	auto stopTime_multi = high_resolution_clock::now();
	duration<double> time_span_multi = duration_cast<duration<double>>(stopTime_multi - startTime_multi);
	std::cout << "-------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Single Core Time: " << time_span_single.count() << " seconds." << std::endl;
	std::cout << "Multi Core Time: " << time_span_multi.count() << " seconds." << std::endl;
	std::cout << "=====================================================================================" << std::endl;
	std::cout << std::endl;
}