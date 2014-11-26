from heapq import heapify, heappush, heappop

INF = 1 << 30

def make_graph():
    return (set(), {})

def V(G):
    return G[0]

def W(G, u, v):
    try:
        return G[1][u][v]
    except KeyError:
        if u == v:
            return 0
        else:
            return INF

def adj(G):
    return G[1]

def add_node(G, u):
    if u not in V(G):
        V(G).add(u)

def is_edge(G, u, v):
    return v in adj(G)[u]

def add_directed_weighted_edge(G, u, v, w):
    try:
        adj(G)[u][v] = w
    except KeyError:
        adj(G)[u] = {v : w}

class HeapEntry:
    # to differentiate entries from each
    # other in case they have the same weight
    counter = 0

    def __init__(self, u, v, w):
        self.u = u
        self.v = v
        self.w = w
        self.c = self.counter
        self.counter += 1

    def __lt__(self, that):
        if self.w < that.w:
            return True
        if that.w < self.w:
            return False
        return self.c < that.c

    def __repr__(self):
        return "(u:{0}, v:{1}, w:{2})".format(self.u, self.v, self.w)

class PathEntry:
    def __init__(self, weight, heapptr):
        self.weight = weight
        self.first = None
        self.heapptr = heapptr

    def __repr__(self):
        return "(wt:{0}, fst:{1}, ptr:{2})".format(self.weight, self.first, self.heapptr)

def build_data_structures(G):
    H, P = [], {}
    for u in V(G):
        for v in V(G):
            weight = W(G, u, v)
            heapptr = None
            if u != v:
                heapptr = HeapEntry(u, v, weight)
                H.append(heapptr)
            try:
                P[u][v] = PathEntry(weight, heapptr)
            except KeyError:
                P[u] = {v : PathEntry(weight, heapptr)}
    heapify(H)
    return H, P, {u : [] for u in V(G)}

def update_heap(H, x, z, w):
    for e in H:
        if e.u == x and e.v == z:
            e.w = w
    heapify(H)

def update(x, y, z, H, P):
    if P[x][y].weight + P[y][z].weight < P[x][z].weight:
        P[x][z].weight = P[x][y].weight + P[y][z].weight
        P[x][z].first = y
        update_heap(H, x, z, P[x][z].weight)

def hidden_paths(G):
    H, P, E = build_data_structures(G)
    while len(H) != 0 and H[0].w != INF:
        e = heappop(H)
        print e.w
        if is_edge(G, e.u, e.v):
            E[e.v].append((e.u, e.v))
            for z in V(G):
                update(e.u, e.v, z, H, P)
        for (t, u) in E[e.u]:
            update(t, e.u, e.v, H, P)
    return P

def path_weight(P, u, v):
    if P[u][v].weight == INF:
        return -1
    return P[u][v].weight

def main():
    import sys
    G = make_graph()
    for line in sys.stdin:
        edge_data = line.strip().split()
        u, v, w = edge_data[0], edge_data[1], int(edge_data[2])
        add_node(G, u)
        add_node(G, v)
        add_directed_weighted_edge(G, u, v, w)
    P = hidden_paths(G)
    for u in V(G):
        for v in V(G):
            print "({0} ~> {1}) : {2}".format(u, v, path_weight(P, u, v))

if __name__ == '__main__':
    main()

