#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include "main.h"
#include <windows.h>
using namespace std;

using namespace std::chrono;
const auto PiValue = 3.141592653589793238;
const auto num_threads = std::thread::hardware_concurrency();
auto max_total_count = 100000550000;

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
double threadRun(int num_threads, int total_count)
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
	return pi_value;
	//std::cout << "Value of PI is: " << pi_value << std::endl;
}
void main()
{
	//auto total_count = 110000055;'
	int counter = 0, counter_total = 0;
	float st_time_total = 0, avg_st_pi = 0, avg_st_acc = 0;
	float mt_time_total, avg_mt_pi, avg_mt_acc;
	double mtCount[100][3];
	double stCount[100][3];
	int totalCount[100];
	int input, multiplier;
	std::cout << "Enter test type: \n [1] Fast Test \n [2] Short Test\n [3] Medium Test\n [4] Long Test\n [5] Extensive Test" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		max_total_count = 10;
		multiplier = 12;
		break;
	case 2:
		max_total_count = 1000;
		multiplier = 6;
		break;
	case 3:
		max_total_count = 10000000;
		multiplier = 3;
		break;
	case 4:
		max_total_count = 1000000000000;
		multiplier = 2;
		break;
	default:
		break;
	}
	ClearScreen();
	for (int total_count = 1; total_count <= max_total_count; total_count *= 10)
	{
		//string progress = "[" + string((total_count / max_total_count) * 100, '=') + string((1 - (total_count / max_total_count)) * 100, ' ') + "]  \n";
		//cout << "\r\033[F" << (total_count / max_total_count) * 100 << "\n" << progress << flush;
		//cout << progress;
		loadingBar(counter, multiplier);
		//std::cout << "=====================================================================================" << std::endl;
		totalCount[counter] = total_count;
		//Single Thread
		auto startTime_single = high_resolution_clock::now();
		double st_pi = threadRun(1, total_count);
		auto stopTime_single = high_resolution_clock::now();
		duration<double> time_span_single = duration_cast<duration<double>>(stopTime_single - startTime_single);
		//std::cout << "Value of PI is: " << st_pi << std::endl;
		auto st_acc = (1 - (abs(PiValue - st_pi) / PiValue)) * 100;
		//std::cout << "Accuracy: " << st_acc << "%" << std::endl;
		stCount[counter][1] = st_pi;
		stCount[counter][2] = st_acc;
		stCount[counter][3] = (double)time_span_single.count();
		/*avg_st_pi += st_pi;
		avg_st_acc += st_acc;
		st_time_total += time_span_single.count();*/
		//Multithreaded
		auto startTime_multi = high_resolution_clock::now();
		double mt_pi = threadRun(num_threads, total_count);
		auto stopTime_multi = high_resolution_clock::now();
		duration<double> time_span_multi = duration_cast<duration<double>>(stopTime_multi - startTime_multi);
		//std::cout << "Value of PI is: " << mt_pi << std::endl;
		auto mt_acc = (1 - (abs(PiValue - mt_pi) / PiValue)) * 100;
		//std::cout << "Accuracy: " << mt_acc << "%" << std::endl;
		mtCount[counter][1] = mt_pi;
		mtCount[counter][2] = mt_acc;
		mtCount[counter][3] = (double)time_span_multi.count();
		//Output
	/*	std::cout << "-------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Single Core Time: " << time_span_single.count() << " seconds." << std::endl;
		std::cout << "Multi  Core Time: " << time_span_multi.count() << " seconds." << std::endl;
		std::cout << "=====================================================================================" << std::endl;*/
		std::cout << std::endl;
		counter++;
		ClearScreen();
	}
	for (int i = 0; i <= 100; ++i)
	{
		//string progress = "[" + string(i, '=') + string(100 - i, ' ') + "]";
		//cout << "\r\033[F" << i << "\n" << progress << flush;
		//usleep(10000);
	}
	//std::cout << "T | Value of PI is: " << avg_st_pi / counter << std::endl;
	//std::cout << "T | Accuracy: " << avg_st_acc / counter << "%" << std::endl;
	//std::cout << "T | Single Core Time: " << st_time_total << " seconds." << std::endl;
	//ClearScreen();
	OutputResults(counter, totalCount, stCount, mtCount);
}

void OutputResults(int counter, int  totalCount[100], double  stCount[100][3], double  mtCount[100][3])
{
	int colWidth = 10;
	cout //<< std::left << std::setw(12) << "Single Core" << std::right << std::setw(3) << "Multi Core" << '\n';
		<< setw(colWidth) << "                           "
		<< setw(colWidth) << "|"
		<< setw(colWidth * 3) << "Single Core"
		<< setw(colWidth) << "|"
		<< setw(colWidth * 3) << "Multi Core"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	//std::cout << std::left << std::setw(12) << 1 << std::right << std::setw(3) << 23 << '\n';

	cout << setprecision(0)
		<< setw(colWidth) << "Points"
		<< setw(colWidth) << "|"
		<< setw(colWidth) << "Value"
		<< setw(colWidth) << "Acc."
		<< setw(colWidth) << "Time "
		<< setw(colWidth) << "|"
		<< setw(colWidth) << "Value"
		<< setw(colWidth) << "Acc."
		<< setw(colWidth) << "Time"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	for (size_t i = 0; i < counter; i++)
	{
		cout << setprecision(0)
			<< setw(colWidth) << totalCount[i]
			<< setw(colWidth) << "|"
			<< setw(colWidth) << stCount[i][1] << setprecision(4)
			<< setw(colWidth) << stCount[i][2] << "%"
			<< setw(colWidth) << stCount[i][3]
			<< setw(colWidth) << "|"
			<< setw(colWidth) << mtCount[i][1] << setprecision(4)
			<< setw(colWidth) << mtCount[i][2] << "%"
			<< setw(colWidth) << mtCount[i][3]
			<< endl;
	}
	cout << "--------------------------------------------------------------------------------------------" << endl;
}

void ClearScreen()
{
	system("clear");
	system("cls");
	cout << "\033[2J\033[1;1H";
}

void loadingBar(int current, int mult)
{
	// 0 - black background,
	// A - Green Foreground
	system("color 0A");

	// Initialize char for printing
	// loading bar
	char a = 177, b = 219;

	printf("\n\n\n\n");
	printf("\n\n\n\n\t\t\t\t\t Loading...\n\n");
	printf("\t\t\t\t\t");

	// Print initial loading bar
	for (int i = 0; i < 24; i++)
		printf("%c", a);

	// Set the cursor again starting
	// point of loading bar
	printf("\r");
	printf("\t\t\t\t\t");

	// Print loading bar progress
	//int temp = (current / total) * 25;
	for (int i = 0; i < current * mult; i++) {
		printf("%c", b);

		// Sleep for 1 second
		//Sleep(1000);
	}
}