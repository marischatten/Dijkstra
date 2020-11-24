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
#include <mpi.h>

#define INFINITY std::numeric_limits<int>::max();

int numVertex;

using namespace std;

class Graph
{
private:
	int _numVertex;

	// fila de prioridades de pair (distancia, vértice)
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> _queuePriority;
	list<pair<int, int>>::iterator _it;
	// ponteiro para um array contendo as listas de adjacências
	list<pair<int, int>> *_lstAdj;

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

struct Edge
{
	int vertex[3];
};

int main(int argc, char *argv[])
{
	numVertex = atoi(argv[1]);
	int allToAll = ((numVertex * numVertex) - numVertex); //desconsidera  x para x quando x=x.
	int result[numVertex][numVertex];
	struct Edge edge[allToAll];
	int send_block[allToAll][3];
	int recv_block[allToAll][3];
	int *pointer = &send_block[0][0];
	//MPI
	int size, rank, orig, dest;
	MPI_Status status;
	int tag = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int fragment = allToAll / (size - 1);
	int mod = allToAll % (size - 1);
	int send_fragment[fragment][3];

	string input = "";
	int values[3];
	string output = "";
	int index = 0;
	int it = 0;

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
		edge[it].vertex[0] = values[0];
		edge[it].vertex[1] = values[1];
		edge[it].vertex[2] = values[2];
		it++;
	}

	MPI_Bcast(edge, allToAll * 3, MPI_INT, 0, MPI_COMM_WORLD); //mestre envia lista de adjacencia para todos - broadcast.

	if (rank == 0)
	{
		int it = 0;
		while (it < allToAll)
		{
			for (orig = 0; orig < numVertex; orig++)
				for (dest = 0; dest < numVertex; dest++)
					if (orig != dest)
					{
						send_block[it][0] = orig;
						send_block[it][1] = dest;
						it++;
					};
		}
		int worker = 1;
		while (worker < size)
		{
			MPI_Send(pointer, fragment * 3, MPI_INT, worker, tag, MPI_COMM_WORLD); // distribui origem e destino.
			pointer += 3;
			worker++;
		}
		if (mod != 0)
		{
			Graph graph(numVertex);
			for (int i = 0; i < allToAll; i++)
				graph.addAresta(edge[i].vertex[0], edge[i].vertex[1], edge[i].vertex[2]);

			int orig, dest;
			for (int i = 0; i < mod; i++)
			{
				orig = *pointer;
				pointer++;
				dest = *pointer;
				pointer++;
				*pointer = graph.dijkstra(orig, dest);
				pointer++;
			}

			for (int i = 0; i < allToAll; i++)
				for (int j = 0; j < 3; j++)
					recv_block[i][j] = send_block[i][j];
		}
	}
	else
	{
		MPI_Recv(&send_fragment, fragment * 3, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

		Graph graph(numVertex);
		for (int i = 0; i < allToAll; i++)
			graph.addAresta(edge[i].vertex[0], edge[i].vertex[1], edge[i].vertex[2]);

		for (int i = 0; i < fragment; i++)
			send_fragment[i][2] = graph.dijkstra(send_fragment[i][0], send_fragment[i][1]); //processos trabalhadores calculam - chamada para dijkstra
	}

	MPI_Gather(&send_fragment, fragment * 3, MPI_INT, &recv_block, fragment * 3, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank != 0)
		MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0)
	{
		MPI_Barrier(MPI_COMM_WORLD);

		//  for (int i = 0; i < allToAll; i++)
		//  	result[recv_block[i][0]][recv_block[i][1]] = recv_block[i][2];
	}
	MPI_Finalize();

	return 0;
}

