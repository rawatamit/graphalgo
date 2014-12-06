#ifndef HIDDEN_PATHS_H
#define HIDDEN_PATHS_H

#include <vector>
#include <iostream>
#include "Heap.h"
#include "ShortestPaths.h"

namespace {

inline bool is_edge(unsigned u, unsigned v, ShortestPaths const* p) {
  return p->get(u, v).first == u;
}

template<typename T>
void build_data_structures(Graph<T> const& g, Heap* heap, ShortestPaths* p) {
  unsigned numv = g.number_of_vertices();
  
  for (unsigned u = 0; u < numv; ++u) {
    // set distance and sigma for (u, u)
    PathEntry& pe = p->get(u, u);
    pe.weight = 0.0;
    p->get(u,u).sigma = 1;

    for (auto const& edge : g.adj_list(u)) {
      unsigned v = edge.other(u);
      double wt = edge.weight();
      HeapEntry* heaptr = new HeapEntry(u, v, wt);
      if (u != v) heap->add(heaptr);
      p->set(u, v, wt, heaptr);
    }
  }
  
  heap->heapify();
}

inline void update(unsigned x, unsigned y, unsigned z, Heap* heap, ShortestPaths* p) {
  PathEntry& xz = p->get(x, z);
  PathEntry& xy = p->get(x, y);
  PathEntry& yz = p->get(y, z);
  bool equal_weight = xz.weight == xy.weight + yz.weight;

  if (is_edge(x, y, p) and equal_weight) {
  //if (x != z and x != y and ) {
    xz.sigma = yz.sigma;
  } else if (is_edge(y, z, p) and equal_weight) {
    xz.sigma = xy.sigma;
  } else if (xz.weight > xy.weight + yz.weight) {
    // we found a path from x to z
    // push a heap entry corresponding to it
    if (xz.heaptr == nullptr) {
      double wt = std::numeric_limits<double>::max();
      xz.heaptr = new HeapEntry(x, z, wt);
      heap->add(xz.heaptr);
    }
    
    xz.weight = xy.weight + yz.weight;
    xz.first = y;
    xz.sigma = 1;
    heap->decreasekey(xz.heaptr, xz.weight);
  }
}

} // anonymous namespace

template<typename T>
ShortestPaths const* hidden_paths(Graph<T> const& g, std::vector<unsigned>* E) {
  unsigned m_star = 0;
  unsigned numv = g.number_of_vertices();
  Heap heap(numv*numv);
  ShortestPaths* p = new ShortestPaths(numv);

  build_data_structures(g, &heap, p);
  while (!heap.empty() and heap.top()->wt != std::numeric_limits<double>::max()) {
      HeapEntry* min = heap.pop();
      unsigned u = min->u, v = min->v;

      if (is_edge(u, v, p)) {
	E[v].push_back(u);
	++m_star; // keep track of m*
	for (auto z = 0; z < numv; ++z) {
	    update(u, v, z, &heap, p);
	}
      }

      for (auto t : E[u]) {
	update(t, u, v, &heap, p);
      }
  }

  //delete[] E;
  return p;
}

#endif
