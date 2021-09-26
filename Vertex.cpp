#include "Vertex.h"

template <typename id_t, typename weight_t>
Vertex<id_t, weight_t>::Vertex() {}

template <typename id_t, typename weight_t>
Vertex<id_t, weight_t>::~Vertex() {}

template <typename id_t, typename weight_t>
void Vertex<id_t, weight_t>::add_edge_to(id_t to_vertex_id, weight_t weight)
{
    adj_map[to_vertex_id] = weight;
}

/*
template <typename id_t, typename weight_t>
bool Vertex<id_t, weight_t>::exists_edge_to(id_t to_vertex_id) const
{
    return false;   //////// temp
}
*/

template <typename id_t, typename weight_t>
const typename std::map<id_t, weight_t>& Vertex<id_t, weight_t>::get_adj_map() const
{
    return adj_map;
}

template class Vertex<int, int>;
template class Vertex<int, unsigned>;
template class Vertex<unsigned, int>;
template class Vertex<unsigned, unsigned>;
template class Vertex<char, int>;