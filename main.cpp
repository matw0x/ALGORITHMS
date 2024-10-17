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

    // ***************************************************************

    const size_t COUNT_VERTICES_3 = 40;
    const size_t COUNT_EDGES_3 = 55;

    char v3[COUNT_VERTICES_3] = { 
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
        'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', 
        '4', '5', '6', '7', '8', '9', '*', '$', '@', '#'
    };
    E e3[COUNT_EDGES_3] = {
        {'A', 'B', 2}, {'A', 'C', 1}, {'B', 'C', 1}, {'B', 'H', 2}, 
        {'C', 'G', 2}, {'C', 'F', 8}, {'D', 'A', 15}, {'E', 'D', 4},
        {'E', 'F', 6.7}, {'F', 'D', 3}, {'G', 'F', 7.5}, {'H', 'G', 0.5},
        {'H', 'J', 2}, {'I', 'E', 4}, {'I', 'F', 11}, {'J', '1', 2},
        {'K', 'M', 3}, {'K', 'I', 2}, {'K', 'E', 6}, {'L', 'M', 6},
        {'M', 'I', 0.5}, {'M', 'G', 0.5}, {'M', 'H', 3}, {'M', 'J', 4},
        {'M', '1', 5}, {'N', 'M', 6}, {'O', 'M', 2.3}, {'P', 'M', 40.4},
        {'Q', 'M', 30.1}, {'R', 'M', 20}, {'S', 'M', 19}, {'S', 'T', 2},
        {'T', 'K', 7.3}, {'U', 'X', 15.6}, {'V', 'U', 3.8}, {'W', 'X', 3.8},
        {'X', 'U', 15.6}, {'Y', 'V', 15.6}, {'Y', 'W', 15.6}, {'Z', 'Y', 2},
        {'0', '*', 1}, {'1', '2', 2}, {'2', 'Z', 2}, {'3', '4', 1},
        {'4', '5', 1}, {'5', '6', 1}, {'6', '7', 1}, {'7', '8', 1},
        {'8', '9', 1}, {'9', '2', 200}, {'9', '0', 1}, {'*', '$', 1},
        {'$', '@', 1}, {'@', '#', 1}, {'#', '3', 1}
    };

    Graph graph3(COUNT_VERTICES_3);
    creating(graph3, v3, e3, COUNT_VERTICES_3, COUNT_EDGES_3);
    std::cout << "GRAPH #3\n";
    graph3.showAdjacencyList();
    // solveWithInput(graph3);
    solveWithCycle(graph3);

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
    for (int i = 0; i <= 5e3; ++i) {
        float x = i * 0.1f;
        g.setLength(x);
        g.DFS_START();
    }

    std::cout << std::endl;
}