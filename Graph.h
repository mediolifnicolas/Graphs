#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <set>
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

    /*
     * Dijkstra implementation using heap data structure
     * O( max(n log(n), e log(n)) )
     * Note: weights must be non negative
     */
    void dijkstra(int from_index) const;

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

    void topological_forest(std::list<int>& result) const;
    void topological(int from_index, bool* visited, std::list<int>& result) const;

    void print_dijkstra_results(std::vector<int>& parent, std::vector<weight_t>& total_cost, unsigned root_index) const;
};

#endif