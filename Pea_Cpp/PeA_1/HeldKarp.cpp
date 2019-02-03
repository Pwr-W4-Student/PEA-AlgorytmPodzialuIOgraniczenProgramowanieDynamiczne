#include "pch.h"
#include "HeldKarp.h"
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>

#define startCity 0



void HeldKarp::ShowRoute()
{
	for (int last = 0; last < G->MatrixSize - 1; ++last) {
		subsetVector[(1 << (G->MatrixSize - 1)) - 1][last].cost = (G->CityMatrix[last][G->MatrixSize - 1] + subsetVector[(1 << (G->MatrixSize - 1)) - 1][last].cost);
	}

	int idOfSubset = (1 << (G->MatrixSize - 1))-1;
	std::vector<int> route;
	std::vector<int> routeOut;
	route.push_back(G->MatrixSize-1);
	while (route.size() != G->MatrixSize)
	{
		
		Subset tmp_min;
		for (int i = 0; i < G->MatrixSize; ++i)
		{
			if (tmp_min.cost > subsetVector[idOfSubset][i].cost)
			{
				tmp_min.cost = subsetVector[idOfSubset][i].cost;
				tmp_min.from = subsetVector[idOfSubset][i].from;
				tmp_min.vertex = subsetVector[idOfSubset][i].vertex;
			}
		}
		route.push_back(tmp_min.vertex);
		idOfSubset = tmp_min.from;
	}
	bool isZero = false;
	std::cout << "Najkrotszy cykl Hamiltonowski o koszcie(BF): " << bestCost << std::endl;

	int offset = 0;
	for (int i = G->MatrixSize - 1, j = 0; i >= 0; i--, j++)
	{
		if (route[i] == 0)
		{
			offset = j;
		}
	}
	for (int i = G->MatrixSize - 1 -offset, j = G->MatrixSize - 1; i >= 0 && j >= 0; i--, j--)
	{
		
			if (i > 0)
			{
				std::cout << route[i];
				if (route[i] != 0 || !isZero)
				{
					std::cout << " -> ";

				}

			}

			else
				std::cout << route[i] << " -> " << route[G->MatrixSize - 1];// << std::endl;

			if(route[i] == 0)
				isZero = true;

		if (i == 0)
		{
			isZero = true;
			i = G->MatrixSize - 1;
			std::cout << " -> ";
		}
		
	}
	std::cout << std::endl;

}

std::string HeldKarp::returnRoute()
{
	for (int last = 0; last < G->MatrixSize - 1; ++last) {
		subsetVector[(1 << (G->MatrixSize - 1)) - 1][last].cost = (G->CityMatrix[last][G->MatrixSize - 1] + subsetVector[(1 << (G->MatrixSize - 1)) - 1][last].cost);
	}

	int idOfSubset = (1 << (G->MatrixSize - 1)) - 1;
	std::vector<int> route;
	route.push_back(G->MatrixSize - 1);
	while (route.size() != G->MatrixSize)
	{

		Subset tmp_min;
		for (int i = 0; i < G->MatrixSize; ++i)
		{
			if (tmp_min.cost > subsetVector[idOfSubset][i].cost)
			{
				tmp_min.cost = subsetVector[idOfSubset][i].cost;
				tmp_min.from = subsetVector[idOfSubset][i].from;
				tmp_min.vertex = subsetVector[idOfSubset][i].vertex;
			}
		}
		route.push_back(tmp_min.vertex);
		idOfSubset = tmp_min.from;
	}


	std::cout << "koszt: " << bestCost << std::endl;
	for (int i = G->MatrixSize - 1; i >= 0; i--)
	{
		if (i > 0)
			std::cout << route[i] << " -> ";
		else
			std::cout << route[i] << " -> " << route[G->MatrixSize - 1] << std::endl;
	}

	std::string res;
	res += "koszt: " + std::to_string(bestCost) + " \n";
	for (int i = G->MatrixSize - 1; i >= 0; i--)
	{
		if (i > 0)
			res += std::to_string(route[i]) + " -> ";
		else
			res += std::to_string(route[i]) + " -> " + std::to_string(route[G->MatrixSize - 1]);

	}
	res += "\n";
	return res;
}

HeldKarp::HeldKarp(Graph * _G)
{
	G = _G;
	subsetVector.resize(1 << (G->MatrixSize - 1), std::vector<Subset>(G->MatrixSize));
	bestCost = INT32_MAX;
}


HeldKarp::~HeldKarp()
{
}

void HeldKarp::Resolve()
{

	int test = (1 << (G->MatrixSize - 1));

	for (int visited = 1; visited < (1 << (G->MatrixSize - 1)); ++visited) //głowna petla, visited = aktualne miasto
	{
		for (int last = 0; last < (G->MatrixSize - 1); ++last) //ostatne miasto nie moze przekroczyc liczby miast
		{

			if (!(visited & 1 << last)) //ostanie miasto musi byc juz odwiedzone
				continue;

			// sprawdzenie wszystkich mozliwosci dla poprzedniego wierzcholka i wybranie najlepszego
			if (visited == 1 << last) {
				// previous vertex must have been N-1
				subsetVector[visited][last].cost = G->CityMatrix[G->MatrixSize - 1][last];
				subsetVector[visited][last].from = (G->MatrixSize - 1);
				subsetVector[visited][last].vertex = last;
			}
			else {
				// poprzedni wierzchołek musi zawierac sie w visited(byc juz sprawdzony)
				int prev_visited = visited ^ 1 << last; //xor
				for (int prev = 0; prev < G->MatrixSize - 1; ++prev) {
					if (!(prev_visited & 1 << prev)) continue;
					subsetVector[visited][last].cost = std::min(
						subsetVector[visited][last].cost,
						G->CityMatrix[prev][last] + subsetVector[prev_visited][prev].cost
					);
					if (subsetVector[visited][last].cost >(G->CityMatrix[prev][last] + subsetVector[prev_visited][prev].cost))
					{
						subsetVector[visited][last].from = visited;
						subsetVector[visited][last].vertex = last;
					}
					else
					{
						subsetVector[visited][last].from = prev_visited;
						subsetVector[visited][last].vertex = last;
					}
				}
			}
		}
	}

	// wybieranie drogi do ostatniego wierzcholka
	for (int last = 0; last < G->MatrixSize - 1; ++last) {
		bestCost = std::min(bestCost, (G->CityMatrix[last][G->MatrixSize - 1] + subsetVector[(1 << (G->MatrixSize - 1)) - 1][last].cost));
	}
}
