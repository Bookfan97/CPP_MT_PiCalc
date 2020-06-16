#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>
#include <chrono>

using namespace std::chrono;
constexpr auto total_count = 10000055;

void doCalcs(int total_iterations, int& in_count_result)
{
	auto seed = std::random_device{}();
	auto gen = std::mt19937{ seed };
	auto dist = std::uniform_real_distribution<>{ 0, 1 };
	auto in_count{ 0 };
	for (auto counter = 0; counter < total_iterations; ++counter) {
		auto x = dist(gen);
		auto y = dist(gen);
		auto result = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
		if (result < 1)
		{
			++in_count;
		}
	}

	in_count_result = in_count;
}
void threadRun(int num_threads)
{
	std::vector<std::thread> threads(num_threads);
	std::vector<int> in_count(num_threads);
	in_count.resize(num_threads);

	for (size_t i = 0; i < num_threads; ++i) {
		int total_iterations = total_count / num_threads;
		if (i == 0) {
			total_iterations += total_count % num_threads;
		}

		threads.emplace_back(doCalcs, total_iterations, std::ref(in_count[i]));
	}

	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}

	double pi_value = 4.0 * static_cast<double>(std::accumulate(in_count.begin(), in_count.end(), 0)) / static_cast<double>(total_count);
	std::cout << "Value of PI is: " << pi_value << std::endl;
}
void main()
{
	std::cout << "=====================================================================================" << std::endl;

	//Single Thread
	auto startTime_single = high_resolution_clock::now();
	threadRun(1);
	auto stopTime_single = high_resolution_clock::now();
	duration<double> time_span_single = duration_cast<duration<double>>(stopTime_single - startTime_single);

	//Multithreaded
	auto num_threads = std::thread::hardware_concurrency();
	auto startTime_multi = high_resolution_clock::now();
	threadRun(num_threads);
	auto stopTime_multi = high_resolution_clock::now();
	duration<double> time_span_multi = duration_cast<duration<double>>(stopTime_multi - startTime_multi);

	//Output
	std::cout << "-------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Single Core Time: " << time_span_single.count() << " seconds." << std::endl;
	std::cout << "Multi  Core Time: " << time_span_multi.count() << " seconds." << std::endl;
	std::cout << "=====================================================================================" << std::endl;
	std::cout << std::endl;
}