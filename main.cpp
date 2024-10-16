#include <iostream>
#include <utility>
#include "graph.h"

typedef std::tuple<char, char, float> E;

void creating(Graph& g, const char* v, const E* e, const size_t& cV, const size_t& cE);
void solveWithInput(Graph& g);
void solveWithCycle(Graph& g);

int main() {
    const size_t COUNT_VERTICES_1 = 6;
    const size_t COUNT_EDGES_1 = 8;

    char v1[COUNT_VERTICES_1] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    E e1[COUNT_EDGES_1] = {
        {'A', 'B', 5}, {'A', 'C', 7}, {'B', 'D', 4}, {'C', 'B', 1}, 
        {'C', 'D', 11}, {'C', 'E', 8}, {'D', 'F', 6}, {'E', 'F', 3}
    };

    Graph graph1(COUNT_VERTICES_1);
    creating(graph1, v1, e1, COUNT_VERTICES_1, COUNT_EDGES_1);
    std::cout << "GRAPH #1\n";
    graph1.showAdjacencyList();
    // solveWithInput(graph1);
    solveWithCycle(graph1);

    // ***************************************************************

    const size_t COUNT_VERTICES_2 = 18;
    const size_t COUNT_EDGES_2 = 21;

    char v2[COUNT_VERTICES_2] = { 
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 
        'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'
    };
    E e2[COUNT_EDGES_2] = {
        {'A', 'G', 7}, {'A', 'D', 8}, {'B', 'D', 7}, {'B', 'O', 6}, 
        {'C', 'P', 13.7}, {'D', 'K', 7.5}, {'E', 'H', 1}, {'F', 'J', 6.3},
        {'G', 'C', 5.5}, {'I', 'Q', 2}, {'I', 'E', 9}, {'I', 'F', 11.4},
        {'J', 'R', 20}, {'L', 'M', 8.2}, {'L', 'N', 18}, {'M', 'R', 10.3},
        {'N', 'R', 5}, {'O', 'D', 10}, {'O', 'P', 4}, {'P', 'L', 5.5},
        {'Q', 'G', 13}
    };

    Graph graph2(COUNT_VERTICES_2);
    creating(graph2, v2, e2, COUNT_VERTICES_2, COUNT_EDGES_2);
    std::cout << "GRAPH #2\n";
    graph2.showAdjacencyList();
    // solveWithInput(graph2);
    solveWithCycle(graph2);

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

void solveWithInput(Graph& g) {
    float x;
    std::cout << "LENGTH FOR GRAPH: "; std::cin >> x;
    g.setLength(x);
    g.DFS_START();

    std::cout << std::endl;
}

void solveWithCycle(Graph& g) {
    for (int i = 0; i <= 1e4; ++i) {
        float x = i * 0.1f;
        g.setLength(x);
        g.DFS_START();
    }

    std::cout << std::endl;
}