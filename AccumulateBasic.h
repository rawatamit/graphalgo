#ifndef ACCUMULATE_BASIC_H
#define ACCUMULATE_BASIC_H

#include "Graph.h"
#include "ShortestPaths.h"
#include <unordered_map>
#include <vector>
#include <limits>
#include <cmath>
#define EPSILON 0.01

template<typename T>
void accumulate_basic(Graph<T> const& g,
                      float* betweenness,
                      std::vector<unsigned>* S,
                      ShortestPaths const* &sp_karger,
                      std::vector<unsigned>* E,
                      unsigned s) {
  /*
    Betweenness is a map.Betweenness[s] gives the betweenness at node s.
    S is a vector.It will be filled with the nodes in topological order.
    P[w] gives a vector of nodes which are the predecessors of w.
    s is the source pertaining to which we have the predecessors.The calling function will call this function for different
    sources
  */
  std::unordered_map<int, float> delta;
  std::unordered_map<int, std::vector<int> > P;
  int numV = g.number_of_vertices();
  
  //Initialize delta
  for(auto const& it : *S) {
    delta[it]=0.0;
  }
  
  // Construct P
  for(unsigned v = 0; v < numV; ++v) {
    for(auto u : E[v]) {
      double weightSU = sp_karger->get(s, u).weight;
      double weightSV = sp_karger->get(s, v).weight;
      double edgeWeight = g.edge_weight(u,v);
      
      if(weightSU != std::numeric_limits<double>::infinity() and weightSV != std::numeric_limits<double>::infinity()) {
        double diff = std::abs(weightSU+edgeWeight-weightSV);
        if(diff <= EPSILON) {
          P[v].push_back(u);
        }
      }
    }
  }

  while(S->size() != 0) {
    int w = S->back();
    S->pop_back();
    
    for(std::vector<int>::iterator it=P[w].begin();it!=P[w].end();++it) {
        int v=*it;
        delta[v]+=(float)sp_karger->get(s,v).sigma*(1.0+delta[w])/sp_karger->get(s,w).sigma;
    }
    
    if(w!=s)
        betweenness[w]+=delta[w];
  }
}

#endif
