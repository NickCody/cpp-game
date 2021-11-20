#include <iostream>
#include <vector>
#include <clocale>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

#if __cplusplus >= 202002L  
static const char* cpp_version = "C++20";
#else
static const char* cpp_version = "Not C++20";
#endif

void addEdgesRandom(Graph& graph, int N) {
    for (int i=0; i < N; i++) {
        graph.addEdge(rand() % graph.numVertices(), rand() % graph.numVertices());
    }
}

int main(int argc, char** argv)
{
    std::setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(0));

    cout << cpp_version << endl;
    
    int V=5;
    int R=V*10;

    if (argc == 2) {
        V = atoi(argv[1]);
        R = V*10;
    } else if (argc == 3) {
        V = atoi(argv[1]);
        R = atoi(argv[2]);
    }

    Graph graph(V, true);
    addEdgesRandom(graph, R);
    graph.printMatrix();
    Graph transposed = graph.transpose();
    transposed.printMatrix();

    return 0;
}