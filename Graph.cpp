#include <iostream>
#include <set>
#include "Graph.h"
#include "Vertex.h"
#include "DijkstraHeap.h"

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
void Graph<id_t, weight_t>::order(Order order_mode, int from_index, bool *visited, int & order_n, vector<int>& result) const
{
    visited[from_index] = true;
    
    if (order_mode == Order::PRE)
    {
        result[from_index] = order_n;
        order_n += 1;
    }

    const map<int, weight_t> adj_map = vertex_arr[from_index].vertex.get_adj_map();
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
        result[from_index] = order_n;
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

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::topological_forest(std::list<int>& result) const
{
    result.resize(0);

    bool* visited = new bool[vertex_count];
    for (unsigned i = 0; i < vertex_count; i++)
        visited[i] = false;

    for (unsigned i = 0; i < vertex_count; i++)
        if (visited[i] == false)
            topological(i, visited, result);

    delete[] visited;
}


template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::topological(int from_index, bool* visited, std::list<int>& result) const
{
    visited[from_index] = true;

    const map<int, weight_t> adj_map = vertex_arr[from_index].vertex.get_adj_map();
    typename map<int, weight_t>::const_iterator it = adj_map.begin();

    while (it != adj_map.end())
    {
        if (visited[it->first] == false)
            topological(it->first, visited, result);
        it++;
    }
    result.push_front(from_index);
}

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::dijkstra(int vertex_id) const
{
    int from_index = get_array_position(vertex_id);

    // Initialization

    DijkstraHeap<weight_t> heap(vertex_count);
    vector<int> parent;
    vector<weight_t> total_cost;

    parent.resize(vertex_count);
    total_cost.resize(vertex_count, 0);

    for (unsigned i = 0; i < vertex_count; i++)
    {
        parent[i] = from_index;
        if (i != from_index)
            heap.add_vertex(i, vertex_arr[from_index].vertex.get_weight_to(i));
    }

    // Iterate n-1 times

    for (int i = 1; i <= vertex_count - 1; i++)
    {
        pair<unsigned, weight_t> w = heap.get_root();
        heap.del_root();
        
        total_cost[w.first] = w.second;

        const std::map<int, weight_t> adj_map = vertex_arr[w.first].vertex.get_adj_map();
        typename map<int, weight_t>::const_iterator it = adj_map.begin();

        while (it != adj_map.end())
        {
            if (heap.exists_vertex(it->first))
            {
                weight_t weight_in_heap = heap.get_weight_to(it->first);

                if (w.second + it->second < weight_in_heap)
                {
                    heap.modify_arbitrary(it->first, w.second + it->second);
                    parent[it->first] = w.first;
                }
            }

            it++;
        }
    }

    print_dijkstra_results(parent, total_cost, from_index);
}

template <typename id_t, typename weight_t>
void Graph<id_t, weight_t>::print_dijkstra_results(vector<int>& parent, vector<weight_t>& total_cost, unsigned root_index) const
{
    for (unsigned vertex = 0; vertex < vertex_count; vertex++)
    {
        cout << "Shortest path to: " << vertex_arr[vertex].vertex_id << endl;
        
        if (total_cost[vertex] != unsigned(-1))
        {
            // Some path found

            cout << "Weight: " << total_cost[vertex] << endl;

            unsigned p = vertex;

            list<unsigned> path;

            while (p != root_index)
            {
                path.push_back(p);
                p = parent[p];
            }
            path.push_back(root_index);

            cout << "Path: ";
            while (!path.empty())
            {
                cout << vertex_arr[path.back()].vertex_id << " ";
                path.pop_back();
            }
            cout << endl << endl;
        }
        else
            cout << "No path found" << endl << endl;

    }
}

template class Graph<int, int>;
template class Graph<int, unsigned>;
template class Graph<unsigned, int>;
template class Graph<unsigned, unsigned>;
template class Graph<char, int>;