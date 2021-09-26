#include <iostream>
#include "Graph.h"
#include "Vertex.h"

constexpr int DEFAULT_VERTEX_RESERVE = 50;

using namespace std;

template <typename id_t, typename weight_t>
Graph<id_t, weight_t>::Graph()
{
    vertex_count = 0;
    vertex_arr.reserve(DEFAULT_VERTEX_RESERVE);
}

template <typename id_t, typename weight_t>
Graph<id_t, weight_t>::~Graph() {}

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::add_vertex(id_t vertex_id)
{
    int index_id = vertex_count;
    vertex_count++;

    id_to_index_map[vertex_id] = index_id;

    VertexWrapper vertex_wrapper;
    Vertex<int, weight_t> vertex;
    
    vertex_wrapper.vertex = vertex;
    vertex_wrapper.vertex_id = vertex_id;

    vertex_arr.push_back(vertex_wrapper);
}

template <typename id_t, typename weight_t>
int Graph<id_t, weight_t>::get_array_position(id_t vertex_id) const
{
    typename map<id_t, int>::const_iterator it = id_to_index_map.find(vertex_id);

    if (it == id_to_index_map.end())
        return -1;
    else
        return it->second;
}

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::add_edge(id_t from_id, id_t to_id, weight_t weight)
{
    int from_index = get_array_position(from_id);
    int to_index = get_array_position(to_id);

    if (from_index != -1 && to_index != -1)
    {
        vertex_arr[from_index].vertex.add_edge_to(to_index, weight);
    }
}

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::print() const
{
    for (unsigned from_index = 0; from_index < vertex_count; from_index++)
    {
        id_t vertex_id = vertex_arr[from_index].vertex_id;

        const map<int, weight_t> adj_map = vertex_arr[from_index].vertex.get_adj_map();
        typename map<int, weight_t>::const_iterator it = adj_map.begin();

        while (it != adj_map.end())
        {
            cout << vertex_id << " -> " << vertex_arr[it->first].vertex_id << " (Weight = " << it->second << ")" << endl;
            it++;
        }

    }
}

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::order_forest(Order order_mode, vector<int>& result) const
{
    // Clear vector and avoid realloc if contains data
    result.resize(0);
    result.resize(vertex_count);

    bool *visited = new bool[vertex_count];
    int order_n = 1;

    for (unsigned i = 0; i < vertex_count; i++)
        visited[i] = false;
    
    for (unsigned i = 0; i < vertex_count; i++)
        if (visited[i] == false)
            order(order_mode, i, visited, order_n, result);

    delete[] visited;
}

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::order(Order order_mode, int from_id, bool *visited, int & order_n, vector<int>& result) const
{
    visited[from_id] = true;
    
    if (order_mode == Order::PRE)
    {
        result[from_id] = order_n;
        order_n += 1;
    }

    const map<int, weight_t> adj_map = vertex_arr[from_id].vertex.get_adj_map();
    typename map<int, weight_t>::const_iterator it = adj_map.begin();

    while (it != adj_map.end())
    {
        int edge_to_index = it->first;
        if (visited[edge_to_index] == false)
            order(order_mode, edge_to_index, visited, order_n, result);
        it++;
    }

    if (order_mode == Order::POST)
    {
        result[from_id] = order_n;
        order_n += 1;
    }
}

template <typename id_t, typename weight_t>
bool Graph<id_t, weight_t>::is_acyclic() const
{
    vector<int> post_order;
    order_forest(Order::POST, post_order);
    bool back_edge_found = false;

    int vertex_index = 0;

    while (vertex_index < vertex_count && back_edge_found == false)
    {
        const map<int, weight_t> adj_map = vertex_arr[vertex_index].vertex.get_adj_map();
        typename map<int, weight_t>::const_iterator it = adj_map.begin();

        while (it != adj_map.end() && back_edge_found == false)
        {
            int edge_to_index = it->first;

            if (post_order[edge_to_index] > post_order[vertex_index])
                back_edge_found = true;

            it++;
        }
        vertex_index++;
    }
    return !(back_edge_found);
}

template class Graph<int, int>;
template class Graph<int, unsigned>;
template class Graph<unsigned, int>;
template class Graph<unsigned, unsigned>;
template class Graph<char, int>;