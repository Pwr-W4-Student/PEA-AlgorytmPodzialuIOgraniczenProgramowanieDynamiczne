#include "pch.h"
#include "Test.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>


Test::Test()
{
	_graph = new Graph;

	BF = new BruteForce(_graph);

	BB = new BranchAndBound(_graph);

	HK = new HeldKarp(_graph);
}


Test::~Test()
{
}

void Test::StartTest()
{
	int testCount = 10;
	std::fstream plik("wynik.txt", std::ios::out);
	if (plik.good())
	{

	std::vector<std::string> *file = new std::vector<std::string>();
	
	/*
	file->push_back("tsp_6_1.txt");
	*/
	file->push_back("tsp_10.txt");
	/*
	file->push_back("tsp_12.txt");
	file->push_back("tsp_13.txt");
	file->push_back("tsp_14.txt");
	file->push_back("tsp_15.txt");
	file->push_back("tsp_17.txt");
	*/
	file->push_back("tsp_21.txt");

	for (int i = 0; i < file->size(); i++)
	{
		fileName = (*file)[i]; ////////////////////////////////////////////////////
		_graph->LoadGraph((*file)[i]);

		plik << fileName + "///////////////////////////////////////// \n";
		plik << "Liczba miast:";
		plik << _graph->MatrixSize << std::endl;

		plik << std::endl << "B&B" << std::endl;
		for (int i = 0; i < testCount; i++)
		{
			std::cout << fileName << " " << i << std::endl;
			Time = 0;
			delete BB;
			BB = new BranchAndBound(_graph);
			StartCounter();
			BB->Resolve();
			Time += GetCounter();
			plik << "Time: ";
			plik << Time << std::endl;
			plik << BB->returnRoute();
		}
		plik << std::endl << std::endl;


	}

		plik.close();
	}
}

void Test::ToFile(std::string data)
{
	std::fstream plik("wynik.txt", std::ios::out);
	if (plik.good())
	{
		plik << data << std::endl;
		plik.close();
	}
}

void Test::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double Test::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}
