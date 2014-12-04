APP=hiddenpath
CXX=clang++
CXXFLAGS=-Wall -g -O0 -std=c++11
OBJS=main.o

$(APP):$(OBJS)
main.o: main.cc Edge.h Graph.h\
	Heap.h ShortestPaths.h\
	Dijkstra.h HiddenPaths.h

$(APP):
	$(CXX) -o $@ $^

clean:
	rm -f $(APP) $(OBJS)
.PHONY: clean
