#include "Graph.h"
#include "Dijkstra.h"
#include "HiddenPaths.h"
#include "AccumulateBasic.h"
#include "TopologicalSort.h"
#include <ctime>
#include <cstdio>
#include <iostream>

// reads .gr files in the following format
// http://www.dis.uniroma1.it/challenge9/format.shtml#graph
/*void read_graph(Graph<std::string>& g, FILE* in) {
  char cmd, buf[4*1024];
  char u[64], v[64];
  double wt;
  
  // skip comment lines
  while (fgets(buf, sizeof buf, in) and buf[0] == 'c')
    ; // empty
  
  // if the next line does not start with p, the graph file
  // is not correct according to the specification
  assert((buf[0] == 'p') or "graph file is corrupted");
  char cmd, tmpbuf[10];
  unsigned n, m;
  sscanf(buf, "%c %s %u %u", &cmd, tmpbuf, &n, &m);

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
}*/

void read_graph(Graph<std::string>& g, FILE* in) {
  char buf[4*1024];
  char u[64], v[64];
  double wt;

  while (fgets(buf, sizeof buf, in)) {
    sscanf(buf, "%s %s %lf", u, v, &wt);
    g.add_node(u);
    g.add_node(v);
    if (wt == 0.0) wt = 1.0;
    g.add_directed_weighted_edge(u, v, wt);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s [options] graph file\n", argv[0]);
    return 1;
  }
  
  const char* filename = argv[1];
  FILE* in = fopen(filename, "r");

  if (in == 0) {
      fprintf(stderr, "error opening file: %s\n", filename);
      return 1;
  }

  Graph<std::string> g;
  read_graph(g, in);
  fclose(in);
  unsigned numv = g.number_of_vertices();
  clock_t begin, end;
  begin = clock();
  std::vector<unsigned>* E = new std::vector<unsigned>[numv];
  ShortestPaths const* sp_karger = hidden_paths(g, E);
  end = clock();
  fprintf(stderr, "karger took %lf\n", (double)(end-begin)/(CLOCKS_PER_SEC));
  
  begin = clock();
  double** sp_dijkstra = dijkstra_all(g);
  end = clock();
  fprintf(stderr, "dijkstra took %lf\n", (double)(end-begin)/(CLOCKS_PER_SEC));
  
  for (unsigned u = 0; u < numv; ++u) {
    for (unsigned v = 0; v < numv; ++v) {
      /*std::cout //<< g.vertex_mapping(u) << ' ' << g.vertex_mapping(v) << ' '
		//<< sp_dijkstra[u][v] << '\n';// << " : "
		<< g.vertex_mapping(u) << ' ' << g.vertex_mapping(v) << ' '
		<< sp_karger->get(u, v).weight << '\n';*/
      if (sp_karger->get(u, v).weight != sp_dijkstra[u][v]) {
        fprintf(stderr, "failed for %s %s, dijkstra gives %lf, karger gives %lf\n",
                  g.vertex_mapping(u).c_str(), g.vertex_mapping(v).c_str(),
                  sp_dijkstra[u][v], sp_karger->get(u, v).weight);
      }
      
      if (sp_karger->get(u, v).sigma > 1)
      //sp_karger->get(u, v).sigma sp_karger->get(u, v).weight
          fprintf(stdout, "%s %s %u\n", g.vertex_mapping(u).c_str(),
            g.vertex_mapping(v).c_str(),
            sp_karger->get(u, v).sigma);
    }
  }
  
  float* betweenness=new float[numv];
  for(unsigned u = 0; u < numv; ++u)
  {
    std::vector<unsigned>* S = dist_sort(sp_karger, numv, u);
    accumulate_basic(g,betweenness,S,sp_karger,E,u);
  }
  
  for (unsigned u = 0; u < numv; ++u)
     fprintf(stdout, "%s %f\n", g.vertex_mapping(u).c_str(), betweenness[u]);

  delete sp_karger;
  
  for (unsigned u = 0; u < numv; ++u)
    delete[] sp_dijkstra[u];
  delete[] sp_dijkstra;
  return 0;
}
