#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <map>
#include <vector>
#include <limits>
#include <cassert>

template <typename T>
class Graph {
private:
    std::vector<T> integermap; // integers to vertices mapping
    std::map<T, unsigned> vertexmap; // vertices to integers mapping
    std::vector<std::vector<Edge>> adj; // adjacency list

public:
    Graph() {
    }

    ~Graph() {
    }

    bool is_node(T const& u) const {
        return vertexmap.count(u) != 0;
    }

    bool is_edge(T const& u, T const& v) const {
        // make sure the vertices are valid
        assert(is_node(u) and is_node(v));

        // get the integer mappings
        unsigned iu = vertexmap[u];
        unsigned iv = vertexmap[v];
        for (auto edge : adj[iu]) {
            if (edge.v == iv)
                return true;
        }
        return false;
    }

    double edge_weight(T const& u, T const& v) const {
        // make sure the vertices are valid
        assert(is_node(u) and is_node(v));

        // get the integer mappings
        unsigned iu = vertexmap[u];
        unsigned iv = vertexmap[v];
        for (auto edge : adj[iu]) {
            if (edge.v == iv)
                return edge.wt;
        }

        // vertices are not connected
        return std::numeric_limits<double>::max();
    }

    unsigned integer_mapping(T const& u) const {
        assert(is_node(u));
        return vertexmap.find(u)->second;
    }

    T const& vertex_mapping(unsigned u) const {
        assert(u >= 0 and u < number_of_vertices());
        return integermap[u];
    }

    std::vector<Edge> const& adj_list(unsigned u) const {
        assert(u >= 0 and u < number_of_vertices());
        return adj[u];
    }

    unsigned number_of_vertices() const {
        // make sure our invariant holds
        assert(integermap.size() == adj.size());
        return integermap.size();
    }

    void add_node(T const& u) {
        if (!is_node(u)) {
            // add to the vertex mapping
            vertexmap[u] = number_of_vertices();

            // and to the integer mapping
            integermap.push_back(u);

            // and add an adjacency list entry
            adj.push_back(std::vector<Edge>());
        }
    }

    void add_directed_weighted_edge(T const& u, T const& v, double wt) {
        // make sure we are adding valid vertices
        assert(is_node(u) and is_node(v));

        // get the integer mappings
        unsigned iu = vertexmap[u];
        unsigned iv = vertexmap[v];
        adj[iu].push_back(Edge(iu, iv, wt));
    }

    void print(std::ostream& out) const {
        for (unsigned u = 0; u < number_of_vertices(); ++u) {
            out << integermap[u] << " : ";
            for (auto edge : adj[u]) {
                out << "(" << integermap[edge.other(u)]
                    << ", " << edge.weight() << ") ";
            }
            out << '\n';
        }
    }
};

#endif
