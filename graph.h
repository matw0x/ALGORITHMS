#pragma once
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
           NE, // кол-во вершин - фактическое (текущее) для дуг
           length; // та самая длина x
    size_t* deletedNumbers; // удалённые индексы | решение проблем с дырами
    size_t deletedCount; // кол-во удалённых

    Vertex* findVertexByName(const char& vertexName) const noexcept {
        for (size_t i = 0; i != countVertices; ++i) {
            if (vertices[i].name == vertexName) return &vertices[i];
        }

        return nullptr;
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

    void showAdjacencyList() const noexcept {
        PRINT_STARS;
        for (size_t i = 0; i != countVertices; ++i) {

            bool noPrint = false;
            for (size_t j = 0; j != deletedCount; ++j) {
                if (deletedNumbers[j] == i) {
                    noPrint = true;
                    break;
                }
            }

            if (noPrint) continue;
            std::cout << vertices[i].name << ": ";

            AdjNode* current = adjLists[i].head;
            if (current == nullptr) {
                std::cout << "NULL";
            } else {
                while (current != nullptr) {
                    std::cout << current->edge->to->name 
                              << '(' << current->edge->cost << ')';

                    if (current->next != nullptr) std::cout << ", ";

                    current = current->next; 
                }
            }

            std::cout << std::endl;
        }
        PRINT_STARS;
    }

    void ADD_V(const char& name) {
        if (NV >= countVertices) {
            std::cout << "ADD_V: Could not add a vertex " << name << " | NV >= countVertices!\n";
            // throw - можно было бы...
            return;
        }

        size_t vertexNumber;
        if (deletedCount > 0) {
            vertexNumber = deletedNumbers[--deletedCount];
        } else if (NV < countVertices) {
            vertexNumber = NV;
        }

        vertices[vertexNumber] = Vertex(name, vertexNumber);
        adjLists[vertexNumber].head = nullptr;
        ++NV;
    }

    void ADD_E(const char& vName, const char& wName, const float& c) {
        if (NE >= countEdges) {
            std::cout << "ADD_E: Could not add an edge from/to " << vName << '/' << wName << " | NE >= countEdges!\n";
            // throw - можно было бы...
            return;
        }

        Vertex* from = findVertexByName(vName);
        Vertex* to = findVertexByName(wName);

        if (from == nullptr) {
            std::cout << "ADD_E: The vertex " << vName << " was not found!\n";
            // throw - можно было бы...
            return;
        }

        if (to == nullptr) {
            std::cout << "ADD_E: The vertex " << wName << " was not found!\n";
            // throw - можно было бы...
            return;
        }

        AdjNode* newNode = new AdjNode(new Edge(from, to, c));
        newNode->next = adjLists[from->number].head;
        adjLists[from->number].head = newNode;
        ++NE;
    }

    void DEL_V(const char& name) {
        Vertex* vertexToDelete = findVertexByName(name);
        if (vertexToDelete == nullptr) {
            std::cout << "DEL_V: The vertex " << name << " was not found!\n";
        }

        // входящие
        for (size_t i = 0; i != NV; ++i) {
            AdjNode* prev = nullptr;
            AdjNode* current = adjLists[i].head;

            while (current != nullptr) {
                if (current->edge->to->name == name) {
                    if (prev == nullptr) {
                        adjLists[i].head = current->next;
                    } else {
                        prev->next = current->next;
                    }

                    delete current;
                    --NE;
                    break;
                }
                
                prev = current;
                current = current->next;
            }
        }

        // исходящая и внутренности
        AdjNode* current = adjLists[vertexToDelete->number].head;
        while (current != nullptr) {
            AdjNode* temp = current;
            current = current->next;
            delete temp;
            --NE;
        }
        
        adjLists[vertexToDelete->number].head = nullptr;
        deletedNumbers[deletedCount++] = vertexToDelete->number;
        --NV;
    }

    void DEL_E(const char& vName, const char& wName) {
        
    }
};