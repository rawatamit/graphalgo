APP=hiddenpath
CXX=clang++
CXXFLAGS=-Wall -g -O3 -DNDEBUG -std=c++11
OBJS=main.o TopologicalSort.o PathEntry.o ShortestPaths.o HeapEntry.o Heap.o

$(APP): $(OBJS)
AccumulateBasic.o: AccumulateBasic.cc AccumulateBasic.h
TopologicalSort.o: TopologicalSort.cc TopologicalSort.h
PathEntry.o: PathEntry.cc PathEntry.h
ShortestPaths.o: ShortestPaths.cc ShortestPaths.h
HeapEntry.o: HeapEntry.cc HeapEntry.h
Heap.o: Heap.cc Heap.h
main.o: main.cc Edge.h Graph.h\
	Heap.h ShortestPaths.h\
	Dijkstra.h HiddenPaths.h \
	TopologicalSort.h AccumulateBasic.h

$(APP):
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(APP) $(OBJS)
.PHONY: clean
