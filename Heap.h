#ifndef HEAP_H
#define HEAP_H

#include "HeapEntry.h"

// Most of the code is converted from the heapq module in python
// Thanks a lot to those people!
// this heap is intricately tied to the hidden paths algorithm
class Heap {
private:
  unsigned size;
  unsigned capacity;
  HeapEntry** array;

  inline void update(HeapEntry* entry, unsigned pos);
  // heap order is maintained for all indices >= startpos
  // except possibly pos
  void siftdown(unsigned startpos, unsigned pos);
  void siftup(unsigned pos);

public:
  Heap(unsigned capacity_);
  virtual ~Heap();

  // simply add the item to the end of the heap
  void add(HeapEntry* item);
  // add the item and maintain the heap invariant
  void add_entry(HeapEntry* item);
  bool empty() const;
  HeapEntry* pop();
  HeapEntry* top();
  void heapify();
  void decreasekey(HeapEntry* item, double wt);
};

#endif
