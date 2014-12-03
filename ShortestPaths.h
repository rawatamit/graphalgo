#ifndef SHORTEST_PATHS_H
#define SHORTEST_PATHS_H

#include <limits>
#include <ostream>
#include <sstream>
#include "Heap.h"

struct PathEntry {
  double weight;
  unsigned first;
  HeapEntry* heaptr;
  
  PathEntry() :
    weight(std::numeric_limits<double>::max()), first(0), heaptr(nullptr) {
  }
  
  PathEntry(double weight_, unsigned first_) :
    weight(weight_), first(first_), heaptr(nullptr) {
  }

  PathEntry(double weight_, unsigned first_, HeapEntry* heaptr_) :
      weight(weight_), first(first_), heaptr(heaptr_) {
  }

  virtual ~PathEntry() {
    delete heaptr;
  }

  friend std::ostream& operator<<(std::ostream& o, PathEntry const& pe) {
      std::stringstream ss;
      ss << '(' << pe.weight << ')';
      return o << ss.str();
  }
};

class ShortestPaths {
private:
  unsigned n;
  PathEntry** paths;

public:
  ShortestPaths(unsigned n_) : n(n_) {
      paths = new PathEntry*[n];
      for (auto i = 0; i < n; ++i) {
	  paths[i] = new PathEntry[n];
      }
  }

  virtual ~ShortestPaths() {
      for (auto i = 0; i < n; ++i)
	  delete[] paths[i];
      delete[] paths;
  }

  PathEntry const& get(unsigned u, unsigned v) const {
      assert(u >= 0 and u < n and v >= 0 and v < n);
      return paths[u][v];
  }

  PathEntry& get(unsigned u, unsigned v) {
      assert(u >= 0 and u < n and v >= 0 and v < n);
      return paths[u][v];
  }

  void set(unsigned u, unsigned v, double wt, HeapEntry* heaptr) {
      assert(u >= 0 and u < n and v >= 0 and v < n);
      paths[u][v].first = u;
      paths[u][v].weight = wt;
      paths[u][v].heaptr = heaptr;
  }
};

#endif
