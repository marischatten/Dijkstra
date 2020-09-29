#include <iostream>
#include <list>
#include <queue>
#include <limits>
#define INFINITY std::numeric_limits<int>::max();

using namespace std;

class Grafo
{
private:
	int _numVertices; // número de vértices
	// ponteiro para um array contendo as listas de adjacências
	list<pair<int, int> > * _lstAdj;

public:

	// construtor
	Grafo(int V)
	{
		this->_numVertices = V; // atribui o número de vértices
		/*
			cria as listas onde cada lista é uma lista de pairs que é um vértice
			onde cada pair é formado pelo vértice destino e o custo
		*/
		_lstAdj = new list<pair<int, int> >[_numVertices];
	}

	// adiciona uma aresta ao grafo de v1 à v2
	void addAresta(int v1, int v2, int custo)
	{
		_lstAdj[v1].push_back(make_pair(v2, custo));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest)
	{
		// vetor de distâncias
		int distance[_numVertices];

		/*
		   vetor de visitados serve para caso o vértice já tenha sido
		   expandido (visitado), não expandir novamente
		*/
		int visited[_numVertices];

		// fila de prioridades de pair (distancia, vértice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > filaPrioridade;

		// inicia o vetor de distâncias e visitados

		//parallel
		for(int i = 0; i < _numVertices; i++)
		{
			distance[i] = INFINITY;
			visited[i] = false;
		}

		// a distância de orig para orig é 0
		distance[orig] = 0;

		// insere na fila
		filaPrioridade.push(make_pair(distance[orig], orig));

		while(!filaPrioridade.empty())
		{
			pair<int, int> p = filaPrioridade.top(); // extrai o pair do topo
			int u = p.second; // obtém o vértice do pair
			filaPrioridade.pop(); // remove da fila

			// verifica se o vértice não foi expandido
			if(visited[u] == false)
			{
				// marca como visitado
				visited[u] = true;

				list<pair<int, int> >::iterator it;

				// percorre os vértices "v" adjacentes de "u"
				for(it = _lstAdj[u].begin(); it != _lstAdj[u].end(); it++)
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// relaxamento (u, v)
					if(distance[v] > (distance[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						distance[v] = distance[u] + custo_aresta;
						filaPrioridade.push(make_pair(distance[v], v));
					}
				}
			}
		}

		// retorna a distância mínima até o destino
		return distance[dest];
	}
};

int main(int argc, char *argv[])
{
	Grafo g(5);

	g.addAresta(0, 1, 4);
	g.addAresta(0, 2, 2);
	g.addAresta(0, 3, 5);
	g.addAresta(1, 4, 1);
	g.addAresta(2, 1, 1);
	g.addAresta(2, 3, 2);
	g.addAresta(2, 4, 1);
	g.addAresta(3, 4, 1);

	cout << g.dijkstra(0, 4) << endl;

	return 0;
}