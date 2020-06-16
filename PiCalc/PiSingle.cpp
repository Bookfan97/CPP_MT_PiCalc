#include "PiSingle.h"

using namespace std;

PiSingle::PiSingle()
{
	runTask();
	numInCircle = getCount();
	area = ((float)numInCircle / NUM_POINTS);
	pi_single = area / (float)0.25;
	cout << "Pi Estimate (Single core): " << pi_single << endl;
}

void PiSingle::runTask()
{
	for (int i = 0; i < NUM_POINTS; i++)
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

int PiSingle::getCount()
{
	return count;
}

int PiSingle::getNumMax()
{
	numMax = numCalc(100, 100);
	return 0;
}

int PiSingle::getNumPoints()
{
	return NUM_POINTS;
}

int PiSingle::numCalc(int x, int y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}