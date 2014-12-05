#ifndef EDGE_H
#define EDGE_H

#include <ostream>
#include <sstream>

class Edge {
private:
  unsigned from, to;
  double wt;

public:
  Edge(unsigned from_, unsigned to_) : from(from_), to(to_), wt(1.0) {
  }

  Edge(unsigned from_, unsigned to_, double wt_) : from(from_), to(to_), wt(wt_) {
  }

  unsigned either() const {
    return from;
  }

  unsigned other(unsigned w) const {
    return w == from ? to : from;
  }

  double weight() const {
    return wt;
  }

  friend std::ostream& operator<<(std::ostream& o, Edge const& e) {
    std::stringstream ss;
    ss << '(' << e.from << ", " << e.to << ", wt:" << e.wt << ')';
    return o << ss.str();
  }
};

#endif
