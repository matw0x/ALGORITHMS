#include <iostream>
#include <utility>
#include "graph.h"

typedef std::tuple<char, char, float> E;

void creating(Graph& g, const char* v, const E* e, const size_t& cV, const size_t& cE);
void solve(const Graph& g, const size_t& n);

int main() {
    float x; // длина для задания
    std::cout << "Input length: "; std::cin >> x;

    const size_t COUNT_VERTICES_1 = 6;
    const size_t COUNT_EDGES_1 = 8;

    char v1[COUNT_VERTICES_1] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    E e1[COUNT_EDGES_1] = {
        {'A', 'B', 5.1}, {'A', 'C', 7}, {'B', 'D', 4.9}, {'C', 'B', 1}, 
        {'C', 'D', 11}, {'C', 'E', 8}, {'D', 'F', 6}, {'E', 'F', 3}
    };

    Graph graph1(COUNT_VERTICES_1, x);
    creating(graph1, v1, e1, COUNT_VERTICES_1, COUNT_EDGES_1);
    solve(graph1, 1);

    return 0;
}

void creating(Graph& g, const char* v, const E* e, const size_t& cV, const size_t& cE) {
    for (size_t i = 0; i != cV; ++i) {
        g.ADD_V(v[i]);
    }

    for (size_t i = 0; i != cE; ++i) {
        g.ADD_E(std::get<0>(e[i]), std::get<1>(e[i]), std::get<2>(e[i]));
    }
}

void solve(const Graph& g, const size_t& n) {
    std::cout << "GRAPH #" << n << std::endl;
    g.showAdjacencyList();
    g.DFS_START();
    std::cout << std::endl;
}