#ifndef EXAMPLEGRAPHS_H
#define EXAMPLEGRAPHS_H

#include "Graph.h"

Graph<char, int> get_graph_1()
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

    return graph;
    /* Copy-Elision :) */
}


Graph<int, int> get_graph_2()
{
    Graph<int, int> graph;

    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);
    graph.add_vertex(6);
    graph.add_vertex(7);
    graph.add_vertex(8);

    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 1);
    graph.add_edge(1, 3, 1);
    graph.add_edge(1, 4, 1);
    graph.add_edge(2, 4, 1);
    graph.add_edge(8, 4, 1);
    graph.add_edge(3, 5, 1);
    graph.add_edge(3, 6, 1);
    graph.add_edge(4, 6, 1);
    graph.add_edge(5, 7, 1);
    graph.add_edge(6, 7, 1);

    return graph;
}


#endif