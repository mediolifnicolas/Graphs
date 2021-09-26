#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include "Vertex.h"

enum class Order { PRE, POST };

template <typename id_t, typename weight_t>
class Graph
{
public:
    Graph();
    ~Graph();
    void add_vertex(id_t vertex_id);
    void add_edge(id_t from_id, id_t to_id, weight_t weight);    
    bool is_acyclic() const;

    void topological_forest(std::list<int>& result) const;

private:

    struct VertexWrapper
    {
        id_t vertex_id;
        Vertex<int, weight_t> vertex;
    };

    typename std::vector<VertexWrapper> vertex_arr;
    unsigned vertex_count;
    
    typename std::map<id_t, int> id_to_index_map;
    int get_array_position(id_t vertex_id) const;

    void order_forest(Order order_mode, std::vector<int>& result) const;
    void order(Order order_mode, int from_index, bool* visited, int& order_n, std::vector<int>& result) const;

    
    void topological(int from_index, bool* visited, std::list<int>& result) const;
};

#endif