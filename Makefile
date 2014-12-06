APP=hiddenpath
CXX=g++
CXXFLAGS=-Wall -g -O3 -DNDEBUG -std=c++11
OBJS=main.o
# accumulateBasic.o topologicalSort.o
# accumulateBasic.o: accumulateBasic.cc
# topologicalSort.o: topologicalSort.cc
$(APP):$(OBJS)
main.o: main.cc Edge.h Graph.h\
	Heap.h ShortestPaths.h\
	Dijkstra.h HiddenPaths.h

$(APP):
	$(CXX) -o $@ $^

clean:
	rm -f $(APP) $(OBJS)
.PHONY: clean
