#include<iostream>
#include"stopwatch.h"
using namespace std;

void StopWatch::start()
{
	start_ = chrono::system_clock::now();
}

unsigned long StopWatch::stop()
{
	end_ = chrono::system_clock::now();
	return (end_ - start_).count();
}

double StopWatch::stopNprint()
{
	end_ = chrono::system_clock::now();
	double r = (end_ - start_).count()/1000.0;
	cout << "lapsed time : " << dec << r << " milliseconds\n";
	return r;
}

