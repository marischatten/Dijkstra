#include <time.h>
#include <iostream>

using namespace std;

void generateGraph(int numVertex)
{
    srand((unsigned)time(NULL));
    int weight = 0;
    double prob = 1; //total de arrestas (vertices * (vertices-1))
    for (int v = 0; v < numVertex; ++v)
        for (int u = 0; u < numVertex; ++u)
            if (v != u)
                if (rand() < prob * (RAND_MAX + 1.0))
                {
                    weight = (rand() % 10 + 1);
                    cout << v << ";" << u << ";" << weight << endl;
                }
}

int main(int argc, char *argv[])
{
    int numVertex = atoi(argv[1]);
    generateGraph(numVertex);
    return 0;
}