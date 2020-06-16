#include "PiMulti.h"

using namespace std;

PiMulti::PiMulti()
{
	numThreads = (std::thread::hardware_concurrency());
	std::thread t_tmp;
	//Based on the Ryzen 9 3950X CPU
	std::thread myThreads[32];
	std::vector<std::thread> threads;
	threads.begin();
	std::thread t[32];
	for (int i = 0; i < numThreads; i++)
	{
		//	//myThreads[i] = (pt.run()); //thread thread(pt.run(), i);
		//	//auto tmp_thread = std::thread(&PiTask::run, i);
		//threads.push_back(move(std::thread(&run)));//&PiTask::run, this));
		//std::thread th(&PiTask/*::run, i);
		//threads.push_back(th);*/
		//threads.push_back(std::thread(). );
		//t[i] = std::thread(runTask);
		//myThreads[i] = std::thread(&run);
		//	//std::thread([this] {this->pt.run(); });
		//	auto handle = std::async(std::launch::async, exec, ping.c_str());
		//	work.push_back(handle.get());
		//run();
	}
	/*for (int i = 0; i < numThreads; i++)
	{
		myThreads[i].join();
	}*/
	for (auto& th : threads) {
		th.join();
	}
	numInCircle = getCount(); //+= getTotal(numThreads);
	//numInCircle = 2;//task1.getCount() + task2.getCount();

	area = ((float)numInCircle / NUM_POINTS);
	pi_multi = area / (float)0.25;
	cout << "Pi Estimate (Multi core): " << pi_multi << endl;
}
void PiMulti::runTask()
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

int PiMulti::getCount()
{
	return count;
}

int PiMulti::getNumMax()
{
	numMax = numCalc(100, 100);
	return 0;
}

int PiMulti::getNumPoints()
{
	return NUM_POINTS;
}

int PiMulti::numCalc(int x, int y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}