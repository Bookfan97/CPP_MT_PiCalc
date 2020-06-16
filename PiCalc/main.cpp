#include <iostream>
#include "PiTask.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

int main()
{
	auto startTime = high_resolution_clock::now();
	PiTask();
	auto stopTime = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(stopTime - startTime);
	std::cout << "Total Time: " << time_span.count() << " seconds.";
	std::cout << std::endl;
}