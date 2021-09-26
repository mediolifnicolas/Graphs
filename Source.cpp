#include <iostream>
#include <list>
#include "Graph.h"
#include "ExampleGraphs.h"

using namespace std;

int main()
{
    Graph<int, int> graph = get_graph_2();

    list<int> t;
    graph.topological_forest(t);

    for (auto q : t)
        cout << q << " ";

    return 0;
}