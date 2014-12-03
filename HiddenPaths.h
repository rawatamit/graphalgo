#ifndef HIDDEN_PATHS_H
#define HIDDEN_PATHS_H

#include <vector>
#include <iostream>
#include "Heap.h"
#include "ShortestPaths.h"

namespace {

template<typename T>
void build_data_structures(Graph<T> const& g, Heap& heap, ShortestPaths& p) {
  unsigned numv = g.number_of_vertices();
  for (unsigned u = 0; u < numv; ++u) {
    for (unsigned v = 0; v < numv; ++v) {
      double wt = g.edge_weight(u, v);
      HeapEntry* heaptr = new HeapEntry(u, v, wt);
      if (u != v) heap.add(heaptr);
      p.set(u, v, wt, heaptr);
    }
  }
  heap.heapify();
}

inline void update(unsigned x, unsigned y, unsigned z, Heap& heap, ShortestPaths& p) {
  PathEntry& xz = p.get(x, z);
  PathEntry& xy = p.get(x, y);
  PathEntry& yz = p.get(y, z);

  if (xz.weight > xy.weight + yz.weight) {
    xz.weight = xy.weight + yz.weight;
    xz.first = y;
    heap.decreasekey(xz.heaptr, xz.weight);
  }
}

inline bool is_edge(unsigned u, unsigned v, ShortestPaths const& p) {
  return p.get(u, v).first == u;
}

} // anonymous namespace

template<typename T>
void hidden_paths(Graph<T> const& g) {
  unsigned numv = g.number_of_vertices();
  Heap heap(numv*numv);
  ShortestPaths p(numv);
  std::vector<unsigned>* E = new std::vector<unsigned>[numv];

  build_data_structures(g, heap, p);
  while (!heap.empty() and heap.top()->wt != std::numeric_limits<double>::max()) {
      HeapEntry* min = heap.pop();
      unsigned u = min->u, v = min->v;

      if (is_edge(u, v, p)) {
	E[v].push_back(u);
	for (auto z = 0; z < numv; ++z) {
	    update(u, v, z, heap, p);
	}
      }

      for (auto t : E[u]) {
	update(t, u, v, heap, p);
      }
  }

  for (auto u = 0; u < numv; ++u) {
    for (auto v : E[u]) {
	std::cout << g.vertex_mapping(v) << ' ' << g.vertex_mapping(u) << ' ' << p.get(v, u) << '\n';
    }
  }

  delete[] E;
}

#endif
