#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <map>
#include <vector>
#include <limits>
#include <cassert>

template <typename T>
class Graph {
// useful typedefs
public:
  typedef std::vector<Edge> AdjListType;

private:
  std::vector<T> intovertex; // integers to vertices mapping
  std::map<T, unsigned> vertexmap; // vertices to integers mapping
  std::vector<AdjListType> adj; // adjacency list

public:
  Graph() {
  }

  ~Graph() {
    intovertex.clear();
    vertexmap.clear();
    adj.clear();
  }

  bool is_node(T const& u) const {
      return vertexmap.count(u) != 0;
  }

  bool is_node(unsigned u) const {
      return u >= 0 and u < number_of_vertices();
  }

  double edge_weight(T const& u, T const& v) const {
      // make sure the vertices are valid
      assert(is_node(u) and is_node(v));
      return edge_weight(vertexmap[u], vertexmap[v]);
  }

  double edge_weight(unsigned u, unsigned v) const {
      // make sure the vertices are valid
      assert(is_node(u) and is_node(v));

      if (u == v) return 0.0;
      for (auto edge : adj[u]) {
	  if (edge.other(u) == v)
	      return edge.weight();
      }
      // vertices are not connected
      return std::numeric_limits<double>::max();
  }

  unsigned integer_mapping(T const& u) const {
      assert(is_node(u));
      return vertexmap.find(u)->second;
  }

  T const& vertex_mapping(unsigned u) const {
    assert(is_node(u));
    return intovertex[u];
  }

  AdjListType const& adj_list(unsigned u) const {
    assert(is_node(u));
    return adj[u];
  }

  unsigned number_of_vertices() const {
    // make sure our invariant holds
    assert(intovertex.size() == adj.size());
    return intovertex.size();
  }

  void add_node(T const& u) {
    if (!is_node(u)) {
      // add to the vertex mapping
      vertexmap[u] = number_of_vertices();

      // and to the integer mapping
      intovertex.push_back(u);

      // and add an adjacency list entry
      adj.push_back(AdjListType());
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
      out << intovertex[u] << " : ";
      for (auto edge : adj[u]) {
	out << "(" << intovertex[edge.other(u)]
	    << ", " << edge.weight() << ") ";
      }
      out << '\n';
    }
  }
};

#endif
