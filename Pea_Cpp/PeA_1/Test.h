#include <string>
#include "Graph.h"
#include "HeldKarp.h"
#include "BranchAndBound.h"
#include "BruteForce.h"


class Test
{
public:
	Test();
	~Test();

	void StartTest();
	void ToFile(std::string data);

private:
	std::string result;
	std::string fileName;

	Graph * _graph = nullptr;
	HeldKarp * HK;
	BranchAndBound * BB;
	BruteForce * BF;


	double PCFreq = 0.0;
	__int64 CounterStart = 0;

	void StartCounter();
	double GetCounter();

	double Time = 0;
};

