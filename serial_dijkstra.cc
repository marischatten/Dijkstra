#include <iostream>
#include <list>
#include <queue>
#include <limits>
#include <time.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <iterator>

#define INFINITY std::numeric_limits<int>::max();

using namespace std;

class Graph
{
private:
	int _numVertex;
	// ponteiro para um array contendo as listas de adjacências
	list<pair<int, int>> *_lstAdj;
	// fila de prioridades de pair (distancia, vértice)
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> _queuePriority;
	list<pair<int, int>>::iterator _it;

public:
	Graph(int v)
	{
		this->_numVertex = v; // atribui o número de vértices
		/*
			cria as listas onde cada lista é uma lista de pairs que é um vértice
			onde cada pair é formado pelo vértice destino e o custo
		*/
		_lstAdj = new list<pair<int, int>>[_numVertex];
	}
	void addAresta(int v1, int v2, int weight)
	{
		_lstAdj[v1].push_back(make_pair(v2, weight));
	}
	int dijkstra(int orig, int dest)
	{
		int distance[_numVertex];
		int visited[_numVertex];
		for (int i = 0; i < _numVertex; i++)
		{
			distance[i] = INFINITY;
			visited[i] = false;
		}
		distance[orig] = 0;
		_queuePriority.push(make_pair(distance[orig], orig));
		while (!_queuePriority.empty())
		{
			pair<int, int> p = _queuePriority.top(); // extrai o pair do topo
			int u = p.second;						 // obtém o vértice do pair
			_queuePriority.pop();					 // remove da fila
			if (visited[u] == false)
			{
				visited[u] = true;
				for (_it = _lstAdj[u].begin(); _it != _lstAdj[u].end(); _it++)
				{
					int v = _it->first;
					int weight_aresta = _it->second;
					if (distance[v] > (distance[u] + weight_aresta))
					{
						distance[v] = distance[u] + weight_aresta;
						_queuePriority.push(make_pair(distance[v], v));
					}
				}
			}
		}
		return distance[dest];
	}
};

int main(int argc, char *argv[])
{
	int numVertex = atoi(argv[1]);
	int orig;
	int dest;
	Graph graph(numVertex);
	string input = "";
	int values[3];
	string output = "";
	int index = 0;
	int result[numVertex][numVertex]; //total de arrestas (vertices * (vertices-1))
	getline(cin, input);
	while (input != "")
	{
		getline(cin, input);
		std::stringstream stream(input);
		while (std::getline(stream, output, ';'))
		{
			values[index] = stoi(output);
			index++;
		}
		index = 0;
		graph.addAresta(values[0], values[1], values[2]);
	}
	
	for (orig = 0; orig < numVertex; orig++)
		for (dest = 0; dest < numVertex; dest++)
		{
			if (orig != dest)
				result[orig][dest] = graph.dijkstra(orig, dest);
			else
				result[orig][dest] = 0;
		}
	return 0;
}