#ifndef DIJKSTRA_HEAP_H
#define DIJKSTRA_HEAP_H

#include <cmath>
#include <iostream>

using namespace std;

constexpr int DEFAULT_HEAP_RESERVE = 100;
constexpr unsigned NON_EXISTANT_VERTEX = -1;

template <typename weight_t>
class DijkstraHeap
{
public:
    DijkstraHeap();
    ~DijkstraHeap();
    DijkstraHeap(unsigned len);

    void add_vertex(unsigned vertex, weight_t weight);
    std::pair<unsigned, weight_t> get_root() const;
    void del_root();
    void del_vertex(unsigned vertex);
    void modify_arbitrary(unsigned vertex, weight_t new_weight);
    bool exists_vertex(unsigned vertex) const;

    weight_t get_weight_to(unsigned to_vertex) const;
    void print() const;
    void print_vertex_position() const;

private:

    std::pair<unsigned, weight_t>* heap_array;
    unsigned heap_len;
    unsigned max_len;

    // Useful to find any vertex heap position in constant time.
    unsigned* vertex_position;

    unsigned relocate(unsigned index);

    // Relocate aiming to the root
    unsigned relocate_up(unsigned index);

    // Relocate aiming to the childs
    unsigned relocate_down(unsigned index);

    bool exists_index(unsigned index) const;

    // Returns zero if no child
    unsigned get_lower_child_index(unsigned index) const;
    void swap_positions(unsigned a, unsigned b);
};



template <typename weight_t>
DijkstraHeap<weight_t>::DijkstraHeap()
{
    heap_array = nullptr;
    vertex_position = nullptr;
    heap_len = 0;
    max_len = 0;
}

template <typename weight_t>
DijkstraHeap<weight_t>::DijkstraHeap(unsigned len)
{
    heap_array = new pair<unsigned, weight_t>[len];
    vertex_position = new unsigned[len];
    for (unsigned i = 0; i < len; i++)
        vertex_position[i] = NON_EXISTANT_VERTEX;
    heap_len = 0;
    max_len = len;
}

template <typename weight_t>
DijkstraHeap<weight_t>::~DijkstraHeap()
{
    delete[] heap_array;
    delete[] vertex_position;
}

template <typename weight_t>
void DijkstraHeap<weight_t>::add_vertex(unsigned vertex, weight_t weight)
{
    heap_array[heap_len] = make_pair(vertex, weight);
    heap_len++;
    vertex_position[vertex] = heap_len - 1;
    relocate_up(heap_len-1);
}

template <typename weight_t>
unsigned DijkstraHeap<weight_t>::relocate_up(unsigned index)
{
    unsigned parent_index = ceil((float(index) + 1) / 2) - 1;
    bool didnt_swap = false;

    while (parent_index != index && !didnt_swap)
    {
        if (heap_array[index].second < heap_array[parent_index].second)
        {
            swap_positions(index, parent_index);
            index = parent_index;
            parent_index = ceil((float(index) + 1) / 2) - 1;
        }
        else
            didnt_swap = true;
    }
    return index;
}

template <typename weight_t>
unsigned DijkstraHeap<weight_t>::relocate_down(unsigned index)
{
    unsigned lower_child_index = get_lower_child_index(index);
    bool didnt_swap = false;

    while (lower_child_index != 0 && !didnt_swap)
    {
        if (heap_array[index].second > heap_array[lower_child_index].second)
        {
            swap_positions(index, lower_child_index);
            index = lower_child_index;
            lower_child_index = get_lower_child_index(index);
        }
        else
            didnt_swap = true;
    }
    return index;
}

template <typename weight_t>
void DijkstraHeap<weight_t>::del_vertex(unsigned vertex)
{
    unsigned vertex_index = vertex_position[vertex];
    swap_positions(vertex_index, heap_len - 1);
    vertex_position[vertex] = NON_EXISTANT_VERTEX;
    heap_len--;
    relocate(vertex_index);
}

template <typename weight_t>
unsigned DijkstraHeap<weight_t>::get_lower_child_index(unsigned index) const
{
    unsigned left_child_index = (index + 1) * 2 - 1;
    unsigned right_child_index = (index + 1) * 2;
    if (exists_index(right_child_index))
        return (heap_array[left_child_index].second > heap_array[right_child_index].second) ?
        right_child_index : left_child_index;
    else
        return (!exists_index(left_child_index)) ? 0 : left_child_index;
}

template <typename weight_t>
void DijkstraHeap<weight_t>::swap_positions(unsigned a, unsigned b)
{
    vertex_position[heap_array[a].first] = b;
    vertex_position[heap_array[b].first] = a;

    pair<unsigned, weight_t> temp = heap_array[a];
    heap_array[a] = heap_array[b];
    heap_array[b] = temp;
}

template <typename weight_t>
unsigned DijkstraHeap<weight_t>::relocate(unsigned index)
{
    unsigned new_index_up = relocate_up(index);
    if (new_index_up != index)
        // Moved closer to the root
        return new_index_up;

    unsigned new_index_down = relocate_down(index);
    return new_index_down;
}

template <typename weight_t>
bool DijkstraHeap<weight_t>::exists_index(unsigned index) const
{
    if (index < heap_len)
        return true;
    return false;
}

template <typename weight_t>
std::pair<unsigned, weight_t> DijkstraHeap<weight_t>::get_root() const
{
    return heap_array[0];
}

template <typename weight_t>
void DijkstraHeap<weight_t>::del_root()
{
    del_vertex(get_root().first);
}

template <typename weight_t>
void DijkstraHeap<weight_t>::print() const
{
    for (unsigned i = 0; i < heap_len; i++)
        cout << "(" << heap_array[i].first << ", " << heap_array[i].second << "),  ";
    cout << endl;
}

template <typename weight_t>
void DijkstraHeap<weight_t>::print_vertex_position() const
{
    for (unsigned i = 0; i < heap_len; i++)
        cout << "Vertex: " << i << ", position: " << vertex_position[i] << endl;
    cout << endl;
}

template <typename weight_t>
weight_t DijkstraHeap<weight_t>::get_weight_to(unsigned to_vertex) const
{
    return heap_array[vertex_position[to_vertex]].second;
}

template <typename weight_t>
void DijkstraHeap<weight_t>::modify_arbitrary(unsigned vertex, weight_t new_weight)
{
    del_vertex(vertex);
    add_vertex(vertex, new_weight);
}

template <typename weight_t>
bool DijkstraHeap<weight_t>::exists_vertex(unsigned vertex) const
{
    if (vertex_position[vertex] != NON_EXISTANT_VERTEX)
        return true;
    return false;
}

#endif