#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Heap.h"
#include <limits>
#include <queue>
#include <iostream>

template<typename T>
double** dijkstra_all(Graph<T> const& g) {
  unsigned numv = g.number_of_vertices();
  double** sp = new double*[numv];
  
  // run dijkstra from all sources
  for (unsigned u = 0; u < numv; ++u)
    sp[u] = dijkstra(g, u);
  
  return sp;
}

template<typename T>
double* dijkstra(Graph<T> const& g, T const& s) {
  return dijkstra(g, g.integer_mapping(s));
}

template<typename T>
double* dijkstra(Graph<T> const& g, unsigned s) {
  unsigned numv = g.number_of_vertices();
  double* distTo = new double[numv];
  unsigned* parent = new unsigned[numv];
  Heap pq(numv);
  HeapEntry** entries = new HeapEntry*[numv];
  
  for (unsigned u = 0; u < numv; ++u) {
    distTo[u] = std::numeric_limits<double>::max();
    parent[u] = u;
    entries[u] = new HeapEntry(u, u, std::numeric_limits<double>::max());
    pq.add(entries[u]);
  }
  
  entries[s]->wt = 0.0;
  pq.heapify();
  distTo[s] = 0.0;
  while (!pq.empty()) {
    HeapEntry* p = pq.pop();
    unsigned u = p->u;

    for (auto const& edge : g.adj_list(u)) {
      unsigned v = edge.other(u);
      double newdist = distTo[u] + edge.weight();
      if (distTo[v] > newdist) {
	distTo[v] = newdist;
	//parent[v] = u;
	pq.decreasekey(entries[v], newdist);
      }
    }
  }
  
  for (unsigned u = 0; u < numv; ++u)
    delete entries[u];
  delete[] entries;
  delete[] parent;
  return distTo;
}

#endif
