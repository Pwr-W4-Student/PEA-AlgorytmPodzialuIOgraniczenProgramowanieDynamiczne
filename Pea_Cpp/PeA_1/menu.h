#pragma once
#include "Graph.h"
#include "HeldKarp.h"
#include "BranchAndBound.h"
#include "BruteForce.h"
#include "Test.h"

class menu
{
private:
	std::string mainMenuStr = " 1. Wczytaj dane z pliku. \n 2. Wyswietl graf \n 3. BruteForce \n 4. BranchAndBound \n 5. Programowanie dynamiczne \n 6. Testy";

	Graph * _graph = nullptr;

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

	void StartCounter();
	double GetCounter();

	void mainMenu();

	HeldKarp * HK;
	BranchAndBound * BB;
	BruteForce * BF;
	Test *test;

public:
	menu();
	~menu();
};

