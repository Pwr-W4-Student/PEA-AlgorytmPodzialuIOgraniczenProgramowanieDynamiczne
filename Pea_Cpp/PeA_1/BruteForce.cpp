#include "pch.h"
#include "BruteForce.h"
#include <cstdint>
#include <iostream>


bool BruteForce::AllCityVisited() //sprawdza czy wszystkie miasta zostaly odwiedzone jezeli tak to zwraca true w przeciwnym razie false
{
	for (int i = 0; i < graph->MatrixSize; i++)
	{
		if (!visitedCities[i])
			return false;
	}
	return true;
}

void BruteForce::Resolve(int v)
{
	if (iteration == 0)
	{
		visitedCities[v] = true;
		tmpRoute[v] = 0;
	}
	iteration++;
	if (!AllCityVisited())
	{
		visitedCities[v] = true;

		for (int c = 0; c < graph->MatrixSize; c++)//czy dane miasto odwiedzone
		{
			if (!visitedCities[c] && graph->CityMatrix[v][c] > 0 && c != v)
			{
				tmpCost += graph->CityMatrix[v][c];
				visitedCities[c] = true;
				tmpRoute[whichCity++] = c;
				Resolve(c);

				tmpCost -= graph->CityMatrix[v][c];//po odwiedzeniu miasta
				visitedCities[c] = false;
				whichCity--;
			}
		}
	}
	else
	{
		tmpCost += graph->CityMatrix[tmpRoute[graph->MatrixSize - 1]] [tmpRoute[0]];
		if (tmpCost < bestCost) //zapisanie najlepszej drogi i jej wartosci
		{
			bestCost = tmpCost;

			for (int i = 0; i < graph->MatrixSize; i++)
				bestRoute[i] = tmpRoute[i];
		}

		tmpCost -= graph->CityMatrix[tmpRoute[graph->MatrixSize - 1]] [tmpRoute[0]];
	}
}

void BruteForce::ShowRoute()
{
	std::cout <<"Najkrótszy cykl Hamiltonowski o koszcie(BF): "<< bestCost<<std::endl;
	for (int i = 0; i < graph->MatrixSize; i++)
	{
		if (i < graph->MatrixSize - 1)
			std::cout << bestRoute[i] << " -> ";
		else
			std::cout<< bestRoute[i] <<" -> " << bestRoute[0] << std::endl;
	}
}

std::string BruteForce::returnRoute()
{
	std::string res;
	res += "koszt: " + std::to_string(bestCost) + " \n";
	for (int i = 0; i < graph->MatrixSize; i++)
	{
		if (i < graph->MatrixSize - 1)
			res += std::to_string( bestRoute[i]) + " -> ";
		else
			res +=  std::to_string( bestRoute[i]) + " -> " + std::to_string( bestRoute[0]);
		
	}
	res += "\n";
	return res;
}

BruteForce::BruteForce(Graph * _G)
{
	graph = _G;
	tmpRoute = new int[graph->MatrixSize];
	visitedCities = new bool[graph->MatrixSize];
	bestRoute = new int[graph->MatrixSize];

	bestCost = INT32_MAX;
	startTop = 0;
	tmpCost = 0;
	whichCity = 1;
	iteration = 0;

	for (int i = 0; i < graph->MatrixSize; ++i)
	{
		tmpRoute[i] = -1;
		visitedCities[i] = false;
		bestRoute[i] = -1;
	}
}


BruteForce::~BruteForce()
{
	delete[] visitedCities;
	delete[] bestRoute;
	delete[] tmpRoute;
}
