#include "Graph.h"
#include "Dijkstra.h"
#include "HiddenPaths.h"
#include <cstdio>
#include <iostream>

// reads .gr files in the following format
// http://www.dis.uniroma1.it/challenge9/format.shtml#graph
void read_graph(Graph<std::string>& g, FILE* in) {
  char cmd, buf[4*1024];
  char u[64], v[64];
  double wt;

  while (fgets(buf, sizeof buf, in)) {// and buf[0] != '\n' and buf[0] != '\0') {
    if (buf[0] != 'c') {
      sscanf(buf, "%c", &cmd);
      
      // add an edge
      if (cmd == 'a') {
	sscanf(buf, "%c %s %s %lf", &cmd, u, v, &wt);
	g.add_node(u);
	g.add_node(v);
	g.add_directed_weighted_edge(u, v, wt);
      }
    }
  }
}

int main(int argc, char* argv[]) {
  const char* filename = "sample.gr";
  FILE* in = fopen(filename, "r");

  if (in == 0) {
      std::cerr << "huh\n";
      return 1;
  }
  
  // read graph size and parameters
  char buf[1024];
  
  // skip comment lines
  while (fgets(buf, sizeof buf, in) and buf[0] == 'c')
    ; /* empty */
  
  // if the next line does not start with p, the graph file
  // is not correct according to the specification
  assert((buf[0] == 'p') or "graph file is corrupted");
  char cmd, tmpbuf[10];
  unsigned n, m;
  sscanf(buf, "%c %s %u %u", &cmd, tmpbuf, &n, &m);

  Graph<std::string> g;
  read_graph(g, in);
  fclose(in);
  //g.print(std::cout);
  //dijkstra(g, std::string("a"));
  hidden_paths(g);

#if 0
  Heap heap(10);
  for (int i = 0; i < 10; ++i) {
    heap.add(new HeapEntry(i, i+1, i));
  }
  heap.heapify();
  while (!heap.empty()) {
    HeapEntry* he = heap.pop();
    std::cout << he->u << ' ' << he->v << ' ' << he->wt << '\n';
  }
#endif

  return 0;
}
