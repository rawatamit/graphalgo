#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "ShortestPaths.h"
#include <algorithm>
#include <utility>
using namespace std;

vector<unsigned>* dist_sort(ShortestPaths const* &sp_karger,unsigned n, unsigned s)
{
  vector< pair<double, unsigned> > result;
  for(unsigned i=0;i<n;i++)
  {
    result.push_back(make_pair(sp_karger->get(s,i).weight,i));
  }
  std::sort(result.begin(),result.end());
  vector<unsigned>* finale = new vector<unsigned>();
  for(unsigned i=0;i<n;i++)
  {
    finale->push_back(result[i].second);
  }
  return finale;
}

#endif
