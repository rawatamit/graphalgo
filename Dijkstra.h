#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <limits>
#include <queue>

template<typename T>
void dijkstra(Graph<T> const& g, T const& s) {
  typedef std::pair<double, unsigned> pdi;

  unsigned numv = g.number_of_vertices();
  double* distTo = new double[numv];
  unsigned* parent = new unsigned[numv];

  for (unsigned i = 0; i < numv; ++i) {
    distTo[i] = std::numeric_limits<double>::max();
    parent[i] = i;
  }

  std::priority_queue<pdi, std::vector<pdi>, std::greater<pdi>> pq;
  unsigned is = g.integer_mapping(s);
  pq.push(std::make_pair(0.0, is));
  distTo[is] = 0.0;
  while (!pq.empty()) {
    pdi p = pq.top(); pq.pop();
    unsigned u = p.second;

    for (auto edge : g.adj_list(u)) {
      unsigned v = edge.other(u);
      if (distTo[v] > distTo[u] + edge.weight()) {
	distTo[v] = distTo[u] + edge.weight();
	parent[v] = u;
	pq.push(std::make_pair(distTo[v], v));
      }
    }
  }

#if 0
    for (unsigned i = 0; i < numv; ++i) {
        if (distTo[i] != std::numeric_limits<double>::max()) {
            std::cout << g.vertex_mapping(parent[i]) << " "
                      << g.vertex_mapping(i) << " "
                      << distTo[i] << "\n";
        }
    }
#endif

  delete[] distTo;
  delete[] parent;
}

#endif
