#include "TopologicalSort.h"
#include <algorithm>

std::vector<unsigned>* dist_sort(ShortestPaths const* &sp_karger, unsigned n, unsigned s) {
  std::vector< std::pair<double, unsigned> > result;
  for(unsigned i=0;i<n;i++) {
    result.push_back(std::make_pair(sp_karger->get(s,i).weight,i));
  }
  
  std::sort(result.begin(),result.end());
  std::vector<unsigned>* finale = new std::vector<unsigned>();
  for(unsigned i=0;i<n;i++) {
    finale->push_back(result[i].second);
  }
  return finale;
}
