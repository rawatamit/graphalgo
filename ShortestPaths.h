#ifndef SHORTEST_PATHS_H
#define SHORTEST_PATHS_H

#include <limits>
#include <ostream>
#include <sstream>
#include "Heap.h"

struct PathEntry {
    double weight;
    int first;
    HeapEntry* heapptr;

    PathEntry() :
        weight(std::numeric_limits<double>::max()),
        first(-1), heapptr(nullptr) {
    }

    PathEntry(double weight_, HeapEntry* heapptr_) :
        weight(weight_), first(-1), heapptr(heapptr_) {
    }

    PathEntry(double weight_, int first_, HeapEntry* heapptr_) :
        weight(weight_), first(first_), heapptr(heapptr_) {
    }

    virtual ~PathEntry() {
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
            for (auto j = 0; j < n; ++j) {
                paths[i][j] = PathEntry();
            }
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

    void set(unsigned u, unsigned v, double wt, HeapEntry* heapptr) {
        assert(u >= 0 and u < n and v >= 0 and v < n);
        paths[u][v].weight = wt;
        paths[u][v].heapptr = heapptr;
    }
};

#endif
