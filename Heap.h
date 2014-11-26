#ifndef HEAP_H
#define HEAP_H

#include <cassert>

struct HeapEntry {
    unsigned u, v;
    double wt;
    unsigned index; // index of the array in the heap data structure

    HeapEntry(unsigned u_, unsigned v_, double wt_) :
        u(u_), v(v_), wt(wt_), index(-1) {
    }

    virtual ~HeapEntry() {
    }

    friend bool operator<(HeapEntry const& a, HeapEntry const& b) {
        if (a.wt < b.wt) return true;
        if (b.wt < a.wt) return false;
        return false;
    }
};

// Most of the code is converted from the heapq module in python
// Thanks a lot to those people!
// this heap is intricately tied to the hidden paths algorithm
class Heap {
private:
    unsigned size;
    unsigned capacity;
    HeapEntry** array;

    inline void update(HeapEntry* entry, unsigned pos) {
        entry->index = pos;
        array[pos] = entry;
    }

public:
    Heap(unsigned capacity_) : size(0), capacity(capacity_) {
        array = new HeapEntry*[capacity];
    }

    virtual ~Heap() {
        delete[] array;
    }

    void add(HeapEntry* item) {
        assert(size >= 0 and size < capacity-1);
        array[size++] = item;
    }

    void heapify() {
        for (int i = size / 2; i >= 0; --i) {
            siftup((unsigned)i);
        }
    }

    void decreasekey(HeapEntry* item, double wt) {
        assert(wt <= item->wt);
        item->wt = wt;
        siftup(item->index);
    }

    // heap order is maintained for all indices >= startpos
    // except possibly pos
    void siftdown(unsigned startpos, unsigned pos) {
        HeapEntry* item = array[pos];
        while (pos > startpos) {
            unsigned parentpos = (pos - 1) >> 1;
            HeapEntry* parent = array[parentpos];
            if (item < parent) {
                update(parent, pos);
                pos = parentpos;
                continue;
            }
            break;
        }
        update(item, pos);
    }

    void siftup(unsigned pos) {
        unsigned startpos = pos;
        HeapEntry* item = array[pos];
        unsigned childpos = 2 * pos + 1;
        while (childpos < size) {
            unsigned rightpos = childpos + 1;
            if (rightpos < size and not (array[childpos] < array[rightpos])) {
                childpos = rightpos;
            }
            // manually update here
            array[pos] = array[childpos];
            array[childpos]->index = pos;
            pos = childpos;
            childpos = 2 * pos + 1;
        }
        update(item, pos);
        siftdown(startpos, pos);
    }
};

#endif
