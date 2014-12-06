#include "HeapEntry.h"

HeapEntry::HeapEntry(unsigned u_, unsigned v_, double wt_) :
  u(u_), v(v_), wt(wt_), index(-1) {
}

HeapEntry::~HeapEntry() {
}

bool operator<(HeapEntry const& a, HeapEntry const& b) {
  if (a.wt < b.wt) return true;
  if (b.wt < a.wt) return false;
  return false;
}
