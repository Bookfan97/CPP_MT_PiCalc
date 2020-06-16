#pragma once
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class PiMulti
{
private:
	std::atomic<long> taskCount;
	int count = 0, numMax, randomPointsToCompute, x, y, num, randNum, numThreads, numInCircle = 0;
	const int NUM_POINTS = 100;
	float areaEstimate = 0.5, area, pi_multi;
public:
	PiMulti();
	int totalCount[];
	void runTask();
	int getCount();
	int getNumMax();
	int getNumPoints();
	int numCalc(int x, int y);
	int getTotal(int totalThreads);
};
