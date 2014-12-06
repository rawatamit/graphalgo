#ifndef HEAP_ENTRY_H
#define HEAP_ENTRY_H

struct HeapEntry {
  unsigned u, v;
  double wt;
  unsigned index; // index of the array in the heap data structure

public:
  HeapEntry(unsigned u_, unsigned v_, double wt_);
  virtual ~HeapEntry();
  friend bool operator<(HeapEntry const& a, HeapEntry const& b);
};

#endif
