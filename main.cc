#include "Graph.h"
#include "Dijkstra.h"
#include "HiddenPaths.h"
#include <sstream>
#include <cstdio>
#include <iostream>

template<typename T>
void read_graph(Graph<T>& g, FILE* in) {
    char buf[4*1024];
    T u, v;
    double wt;

    while (fgets(buf, sizeof buf, in)) {
        std::stringstream stream(buf);
        stream >> u >> v >> wt;
        g.add_node(u);
        g.add_node(v);
        g.add_directed_weighted_edge(u, v, wt);
    }
}

int main(int argc, char* argv[]) {
    const char* filename = "hidden.txt";
    FILE* in = fopen(filename, "r");

    if (in == 0) {
        std::cerr << "huh\n";
        return 1;
    }

    Graph<std::string> g;
    read_graph(g, in);
    fclose(in);
    //g.print(std::cout);
    //dijkstra(g, std::string("a"));
    return 0;
}
