#ifndef PATH_ENTRY_H
#define PATH_ENTRY_H

#include "HeapEntry.h"
#include <ostream>

struct PathEntry {
  double weight;
  unsigned sigma;
  unsigned first;
  HeapEntry* heaptr;

public:
  PathEntry();
  PathEntry(double weight_, unsigned first_);
  PathEntry(double weight_, unsigned first_, HeapEntry* heaptr_);
  virtual ~PathEntry();
  friend std::ostream& operator<<(std::ostream& o, PathEntry const& pe);
};

#endif
