#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "ShortestPaths.h"
#include <vector>

std::vector<unsigned>* dist_sort(ShortestPaths const* &sp_karger, unsigned n, unsigned s);

#endif
