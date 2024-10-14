#include <iostream>
#include <string>
#include "vertex.h"
#include "edge.h"
#include "adjacency_list.h"

const std::string stars(30, '*'); // для удобного вывода
#define PRINT_STARS std::cout << stars + '\n';

class Graph {
private:
    Vertex* vertices; // все вершины
    AdjList* adjLists; // массив списков смежности (для каждой вершины отдельный список)
    size_t countVertices, // кол-во вершин - исходное
           countEdges, // кол-во дуг - исходное
           NV, // кол-во вершин - фактическое (текущее) для вершин
           NE, // кол-во дуг - фактическое (текущее)
           length; // длина (для задания)
    size_t* deletedNumbers; // удалённые индексы | решение проблем с дырами
    size_t deletedCount; // кол-во удалённых вершин

    Vertex* findVertexByName(const char& vertexName) const noexcept {
        for (size_t i = 0; i < countVertices; ++i) {
            if (vertices[i].name == vertexName && vertices[i].name != '-') {
                return &vertices[i];
            }
        }

        return nullptr;
    }

    void removeEdgeToVertex(const Vertex& fromVertex, Vertex* toDelete) {
        AdjNode* current = adjLists[fromVertex.number].head;
        AdjNode* prev = nullptr;
        
        while (current != nullptr) {
            if (current->edge->to == toDelete) {
                std::cout << "[DEBUG] Deleting edge to " << toDelete->name << " from " << fromVertex.name << std::endl;
                if (prev == nullptr) {
                    adjLists[fromVertex.number].head = current->next;
                } else {
                    prev->next = current->next;
                }

                delete current;
                --NE;
                return;
            }

            prev = current;
            current = current->next;
        }
    }

public:
    Graph(const size_t& cV, const size_t& x) : 
    countVertices(cV), countEdges(cV*cV - cV), NE(NV = 0), length(x), deletedCount(0) {
        vertices = new Vertex[countVertices];
        adjLists = new AdjList[countVertices];
        deletedNumbers = new size_t[countVertices];
    }

    ~Graph() {
        for (size_t i = 0; i != NV; ++i) adjLists[i].~AdjList();

        delete[] adjLists;
        delete[] vertices;
        delete[] deletedNumbers;
    }

    void showAdjacencyList() const {
        PRINT_STARS;
        for (size_t i = 0; i < countVertices; ++i) {
            if (vertices[i].name == '-') {
                continue;
            }

            std::cout << vertices[i].name << ": ";
            AdjNode* current = adjLists[i].head;

            if (current == nullptr) {
                std::cout << "NULL";
            } else {
                while (current != nullptr) {
                    std::cout << current->edge->to->name << "(" << current->edge->cost << ")";
                    if (current->next != nullptr) std::cout << ", ";
                    current = current->next;
                }
            }
            std::cout << std::endl;
        }
        PRINT_STARS;
    }

    void ADD_V(const char& name) {
        std::cout << "[DEBUG] Attempting to add vertex: " << name << std::endl;
        for (size_t i = 0; i < countVertices; ++i) {
            if (vertices[i].name == name) {
                std::cout << "[ERROR] ADD_V: Vertex " << name << " already exists!\n";
                return;
            }
        }

        if (deletedCount > 0) {
            size_t index = deletedNumbers[--deletedCount];
            vertices[index].name = name;
            adjLists[index].head = nullptr; // новый список смежности
            ++NV;
            std::cout << "[DEBUG] ADD_V: Vertex " << name << " restored at index " << index << "!\n";
            return;
        }

        if (NV < countVertices) {
            vertices[NV].name = name;
            vertices[NV].number = NV;
            adjLists[NV].head = nullptr; // новый список смежности
            ++NV;
            std::cout << "[DEBUG] ADD_V: Vertex " << name << " added!\n";
        } else {
            std::cout << "[ERROR] ADD_V: Could not add a vertex " << name << " | NV >= countVertices!\n";
        }
    }

    void ADD_E(const char& vName, const char& wName, const float& c) {
        std::cout << "[DEBUG] Attempting to add edge from " << vName << " to " << wName << " with cost " << c << std::endl;

        if (NE >= countEdges) {
            std::cout << "[ERROR] ADD_E: Could not add an edge from/to " << vName << '/' << wName << " | NE >= countEdges!\n";
            return;
        }

        Vertex* from = findVertexByName(vName);
        Vertex* to = findVertexByName(wName);

        if (from == nullptr) {
            std::cout << "[ERROR] ADD_E: The vertex " << vName << " was not found!\n";
            return;
        }

        if (to == nullptr) {
            std::cout << "[ERROR] ADD_E: The vertex " << wName << " was not found!\n";
            return;
        }

        if (from->name == '-' || to->name == '-') {
            std::cout << "[ERROR] ADD_E: One of the vertices is deleted!\n";
            return;
        }

        AdjNode* newNode = new AdjNode(new Edge(from, to, c));
        newNode->next = adjLists[from->number].head;
        adjLists[from->number].head = newNode;
        ++NE;
        std::cout << "[DEBUG] Edge added: " << vName << " -> " << wName << "(" << c << ")\n";
    }

    void DEL_V(const char& name) {
        std::cout << "[DEBUG] Attempting to delete vertex: " << name << std::endl;
        Vertex* vertexToDelete = findVertexByName(name);
        if (vertexToDelete == nullptr) {
            std::cout << "[ERROR] DEL_V: The vertex " << name << " was not found!\n";
            return;
        }

        // исходящие дуги
        std::cout << "[DEBUG] Deleting outgoing edges from vertex: " << name << std::endl;
        AdjNode* current = adjLists[vertexToDelete->number].head;
        while (current != nullptr) {
            AdjNode* temp = current;
            current = current->next;
            std::cout << "[DEBUG] Deleting edge from " << name << " to " << temp->edge->to->name << std::endl;
            delete temp;
            --NE;
        }

        adjLists[vertexToDelete->number].head = nullptr;

        // входящие дуги
        std::cout << "[DEBUG] Deleting incoming edges to vertex: " << name << std::endl;
        for (size_t i = 0; i < NV; ++i) {
            if (i != vertexToDelete->number) {
                removeEdgeToVertex(vertices[i], vertexToDelete);
            }
        }

        vertexToDelete->name = '-';
        deletedNumbers[deletedCount++] = vertexToDelete->number;
        --NV;
        std::cout << "[DEBUG] Vertex " << name << " deleted successfully!\n";
    }


};

const size_t COUNT_VERTICES = 6;

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
    graph.DEL_V('B');
    graph.DEL_V('A');
    graph.DEL_V('E');
}

void test2(Graph& graph) {
    graph.ADD_V('B');
    graph.ADD_E('B', 'D', 4);
}

void test3(Graph& graph) {
    graph.ADD_V('X');
    graph.ADD_V('X');
    graph.ADD_V('Y');
    graph.ADD_V('Z');
    graph.ADD_V('Q');
}

int main() {
    Graph graph(COUNT_VERTICES, 3);
    creating(graph);
    graph.showAdjacencyList();

    test1(graph);
    graph.showAdjacencyList();

    test2(graph);
    graph.showAdjacencyList();

    test3(graph);
    graph.showAdjacencyList();
}
