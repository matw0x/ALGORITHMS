#include <iostream>
#include "graph.h"

const size_t COUNT_VERTICES = 6;

void creating(Graph&);
void test1(Graph&);
void test2(Graph&);
void test3(Graph&);
void test4(Graph&);

int main() {
    size_t x; // длина для задания
    std::cout << "Input length: "; std::cin >> x;

    Graph graph(COUNT_VERTICES, x);

    creating(graph);
    graph.showAdjacencyList();

    test1(graph);
    graph.showAdjacencyList();

    test2(graph);
    graph.showAdjacencyList();

    test3(graph);
    graph.showAdjacencyList();

    test4(graph);

    return 0;
}

void creating(Graph& graph) {
    graph.ADD_V('A');
    graph.ADD_V('B');
    graph.ADD_V('C');
    graph.ADD_V('D');
    graph.ADD_V('E');
    graph.ADD_V('F');

    graph.ADD_E('A', 'B', 5);
    graph.ADD_E('A', 'C', 7);
    graph.ADD_E('B', 'D', 4);
    graph.ADD_E('C', 'B', 1);
    graph.ADD_E('C', 'D', 11);
    graph.ADD_E('C', 'E', 8);
    graph.ADD_E('D', 'F', 6);
    graph.ADD_E('E', 'F', 3);
}

void test1(Graph& graph) {
    graph.DEL_V('A');
}

void test2(Graph& graph) {
    graph.ADD_V('A');
    graph.ADD_E('A', 'C', 7);
    graph.ADD_E('A', 'B', 5);
}

void test3(Graph& graph) {
    graph.EDIT_E('A', 'C', 100);
}

void test4(Graph& graph) {
    graph.DFS_START();
}