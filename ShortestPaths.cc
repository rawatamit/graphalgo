#include "ShortestPaths.h"
#include <cassert>

ShortestPaths::ShortestPaths(unsigned n_) : n(n_) {
  paths = new PathEntry*[n];
  for (unsigned i = 0; i < n; ++i) {
    paths[i] = new PathEntry[n];
  }
}

ShortestPaths::~ShortestPaths() {
  for (unsigned i = 0; i < n; ++i)
    delete[] paths[i];
  delete[] paths;
}

PathEntry const& ShortestPaths::get(unsigned u, unsigned v) const {
  assert(u >= 0 and u < n and v >= 0 and v < n);
  return paths[u][v];
}

PathEntry& ShortestPaths::get(unsigned u, unsigned v) {
  assert(u >= 0 and u < n and v >= 0 and v < n);
  return paths[u][v];
}

void ShortestPaths::set(unsigned u, unsigned v, double wt, HeapEntry* heaptr) {
  assert(u >= 0 and u < n and v >= 0 and v < n);
  paths[u][v].first = u;
  paths[u][v].weight = wt;
  paths[u][v].heaptr = heaptr;
}
