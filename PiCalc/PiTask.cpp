#include "PiTask.h"

using namespace std;

PiTask::PiTask()
{
	numThreads = (std::thread::hardware_concurrency());
	//Based on the Ryzen 9 3950X CPU
	//std::thread myThreads[32];
	std::vector<std::thread> threads(numThreads);
	for (int i = 0; i < numThreads - 1; i++)
	{
		//	//myThreads[i] = (pt.run()); //thread thread(pt.run(), i);
		//	//auto tmp_thread = std::thread(&PiTask::run, i);
		threads.push_back(std::thread());//&PiTask::run, this));
		//	//std::thread([this] {this->pt.run(); });
		//	auto handle = std::async(std::launch::async, exec, ping.c_str());
		//	work.push_back(handle.get());
		run();
	}
	/*for (int i = 0; i < numThreads; i++)
	{
		myThreads[i].join();
	}*/
	/*for (auto& th : threads) {
		th.join();
	}*/
	numInCircle = getCount(); //+= getTotal(numThreads);
	//numInCircle = 2;//task1.getCount() + task2.getCount();

	area = ((float)numInCircle / NUM_POINTS);
	pi = area / (float)0.25;
	cout << "Pi (est): " << pi << endl;
}

void PiTask::run()
{
	for (int i = 0; i < NUM_POINTS / numThreads; i++)
	{
		x = rand() % 200;
		y = rand() % 200;
		num = numCalc(x, y);
		if (num < 200)
		{
			count++;
		}
	}
}

int PiTask::getCount()
{
	return count;
}

int PiTask::getNumMax()
{
	numMax = numCalc(100, 100);
	return 0;
}

int PiTask::getNumPoints()
{
	return NUM_POINTS;
}

int PiTask::numCalc(int x, int y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

int PiTask::getTotal(int totalThreads)
{
	int total = 0;
	for (int i = 0; i < totalThreads; i++)
	{
		total += totalCount[i];
	}
	return total;
}