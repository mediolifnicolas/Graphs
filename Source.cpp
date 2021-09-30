#include <iostream>
#include <list>
#include "Graph.h"
#include "ExampleGraphs.h"
#include "DijkstraHeap.h"

using namespace std;

int main()
{
    Graph<int, unsigned> graph = get_graph_4();
    graph.dijkstra(3);

    return 0;
}