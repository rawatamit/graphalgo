#ifndef HIDDEN_PATHS_H
#define HIDDEN_PATHS_H

#include "Heap.h"
#include "ShortestPaths.h"

namespace {

template<typename T>
void build_data_structures(Graph<T> const& g, Heap& heap, ShortestPaths& p) {
    unsigned numv = g.number_of_vertices();
    for (auto u = 0; u < numv; ++u) {
        for (auto edge : g.adj_list(u)) {
            HeapEntry* heapptr = new HeapEntry(u, edge.other(u), edge.weight());
            heap.add(heapptr);
            p.set(u, edge.other(u), edge.weight(), heapptr);
        }
    }
    heap.heapify();
}

} // anonymous namespace

template<typename T>
void hidden_paths(Graph<T> const& g) {
}

#endif
