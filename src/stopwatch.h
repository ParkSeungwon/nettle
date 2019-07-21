#pragma once
#include<chrono>

class StopWatch
{
public:
	void start();
	unsigned long stop();
	double stopNprint();

protected:
	std::chrono::system_clock::time_point start_, end_;
};
