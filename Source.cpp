#include <iostream>
#include <list>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<char, int> graph;

    graph.add_vertex('a');
    graph.add_vertex('b');
    graph.add_vertex('c');
    graph.add_vertex('d');
    graph.add_vertex('e');
    graph.add_vertex('f');

    graph.add_edge('a', 'b', 1);
    graph.add_edge('a', 'd', 1);
    graph.add_edge('b', 'c', 1);
    graph.add_edge('c', 'b', 1);
    graph.add_edge('b', 'd', 1);
    graph.add_edge('d', 'e', 1);
    graph.add_edge('e', 'c', 1);
    graph.add_edge('f', 'c', 1);
    graph.add_edge('d', 'f', 1);

    cout << graph.is_acyclic();

    return 0;
}