#ifndef VERTEX_H
#define VERTEX_H

#include <map>

template <typename id_t, typename weight_t>
class Vertex
{
public:
    Vertex();
    ~Vertex();
    void add_edge_to(id_t to_vertex_id, weight_t weight);
    bool exists_edge_to(id_t to_vertex_id) const;
    weight_t get_weight_to(id_t to_vertex_id) const;
    const typename std::map<id_t, weight_t>& get_adj_map() const;
private:
    typename std::map<id_t, weight_t> adj_map;
};


#endif