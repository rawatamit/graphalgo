#ifndef SHORTEST_PATHS_H
#define SHORTEST_PATHS_H

#include "PathEntry.h"
#include "HeapEntry.h"

class ShortestPaths {
private:
  unsigned n;
  PathEntry** paths;

public:
  ShortestPaths(unsigned n_);
  virtual ~ShortestPaths();
  PathEntry const& get(unsigned u, unsigned v) const;
  PathEntry& get(unsigned u, unsigned v);
  void set(unsigned u, unsigned v, double wt, HeapEntry* heaptr);
};

#endif
