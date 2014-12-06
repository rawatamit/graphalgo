#include "PathEntry.h"
#include <limits>
#include <sstream>

PathEntry::PathEntry() :
  weight(std::numeric_limits<double>::max()), sigma(0), first(0), heaptr(nullptr) {
}

PathEntry::PathEntry(double weight_, unsigned first_) :
  weight(weight_), sigma(0), first(first_), heaptr(nullptr) {
}

PathEntry::PathEntry(double weight_, unsigned first_, HeapEntry* heaptr_) :
  weight(weight_), sigma(0), first(first_), heaptr(heaptr_) {
}

PathEntry::~PathEntry() {
  delete heaptr;
}

std::ostream& operator<<(std::ostream& o, PathEntry const& pe) {
  std::stringstream ss;
  ss << '(' << pe.weight << ')';
  return o << ss.str();
}
