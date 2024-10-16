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
           NE; // кол-во вершин - фактическое (текущее) для дуг
    float length; // та самая длина x
    size_t* deletedNumbers; // удалённые индексы | решение проблем с дырами
    size_t deletedCount; // кол-во удалённых

    const size_t UNREAL_VALUE = this->countVertices + 1; // для неопределённых индексов

    Vertex* findVertexByName(const char& vertexName) const noexcept {
        for (size_t i = 0; i != countVertices; ++i) {
            if (vertices[i].name == vertexName && vertices[i].name != '-') return &vertices[i];
        }

        return nullptr;
    }

    void DFS(const size_t& currentIndex, size_t* path, size_t& pathLength, float& currentCost) const noexcept {
        vertices[currentIndex].setVisited();
        path[pathLength++] = currentIndex;

        auto getEdgeCost = [&](const size_t& from, const size_t& to) -> float {
            AdjNode* current = adjLists[from].head;
            while (current != nullptr) {
                if (current->edge->to->number == to) {
                    return current->edge->cost;
                }
                current = current->next;
            }
            return 0.0f;
        };

        if (currentCost == length) {
            if (path[0] != currentIndex) {
                std::cout << "DFS | x = " << length << " | ";
                for (size_t i = 0; i != pathLength; ++i) {
                    std::cout << vertices[path[i]].name << ' ';
                }

                std::cout << std:: endl;
                PRINT_STARS;
            }
        } else if (currentCost < length) {
            size_t i = FIRST(vertices[currentIndex].name);
            while (i != UNREAL_VALUE) {
                if (!vertices[i].visited) {
                    float edgeCost = getEdgeCost(currentIndex, i);
                    currentCost += edgeCost;
                    DFS(i, path, pathLength, currentCost);
                    currentCost -= edgeCost; // откатываем вес дуги после рекурсии
                }

                i = NEXT(vertices[currentIndex].name, i);
            }
        }

        vertices[currentIndex].visited = false;
        --pathLength;
    }

public:
    Graph(const size_t& cV) : 
    countVertices(cV), countEdges(cV*cV - cV), deletedCount(NE = NV = 0) {
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
        for (auto it = VertexIterator::begin(vertices, countVertices); 
            it != VertexIterator::end(vertices, countVertices); 
            ++it) {
            
            std::cout << (*it).name << ": ";

            bool isEmpty = true;
            for (auto adjIt = AdjListIterator::begin(adjLists[(*it).number].head); 
                adjIt != AdjListIterator::end(); 
                ++adjIt) {
                isEmpty = false; // т.к. иное не может в принципе зайти в цикл

                std::cout << (*adjIt)->edge->to->name 
                        << '(' << (*adjIt)->edge->cost << ')';
                
                if ((*adjIt)->next != nullptr) std::cout << ", ";
            }

            if (isEmpty) std::cout << "NULL";
            std::cout << std::endl;
        }
        PRINT_STARS;
    }

    void ADD_V(const char& name) noexcept {
        for (size_t i = 0; i != countVertices; ++i) {
            if (vertices[i].name == name) {
                std::cout << "ADD_V: Vertex " << name << " already exists!\n";
            }
        }
        
        if (deletedCount > 0) {
            size_t vertexNumber = deletedNumbers[--deletedCount];
            vertices[vertexNumber].name = name;
            adjLists[vertexNumber].head = nullptr;
            ++NV;
            return;
        }

        if (NV >= countVertices) {
            std::cout << "ADD_V: Could not add a vertex " << name << " | NV >= countVertices!\n";
            return;
        } else {
            vertices[NV].name = name;
            vertices[NV].number = NV;
            adjLists[NV++].head = nullptr;
        }
    }

    void ADD_E(const char& vName, const char& wName, const float& c) noexcept {
        if (NE >= countEdges) {
            std::cout << "ADD_E: Could not add an edge from/to " << vName << '/' << wName << " | NE >= countEdges!\n";
            return;
        }

        Vertex* from = findVertexByName(vName);
        Vertex* to = findVertexByName(wName);

        if (from == nullptr) {
            std::cout << "ADD_E: The vertex " << vName << " was not found!\n";
            return;
        }

        if (to == nullptr) {
            std::cout << "ADD_E: The vertex " << wName << " was not found!\n";
            return;
        }

        if (from->name == '-' || to->name == '-') {
            std::cout << "ADD_E: One of the vertices " << '[' << vName 
            << ", " << wName << "] is deleted!\n";
            return;
        }

        AdjNode* newNode = new AdjNode(new Edge(from, to, c));
        newNode->next = adjLists[from->number].head;
        adjLists[from->number].head = newNode;
        ++NE;
    }

    void DEL_V(const char& name) noexcept {
        Vertex* vertexToDelete = findVertexByName(name);
        if (vertexToDelete == nullptr) {
            std::cout << "DEL_V: The vertex " << name << " was not found!\n";
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

        // входящие
        for (size_t i = 0; i != NV; ++i) {
            if (i != vertexToDelete->number) {
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
        }
        
        vertexToDelete->name = '-';
        deletedNumbers[deletedCount++] = vertexToDelete->number;
        --NV;
    }

    void DEL_E(const char& vName, const char& wName) noexcept {
        Vertex* from = findVertexByName(vName);
        Vertex* to = findVertexByName(wName);

        if (from == nullptr) {
            std::cout << "ADD_E: The vertex " << vName << " was not found!\n";
            return;
        }

        if (to == nullptr) {
            std::cout << "ADD_E: The vertex " << wName << " was not found!\n";
            return;
        }

        if (from->name == '-' || to->name == '-') {
            std::cout << "ADD_E: One of the vertices " << '[' << vName 
            << ", " << wName << "] is deleted!\n";
            return;
        }

        AdjNode* prev = nullptr;
        AdjNode* current = adjLists[from->number].head;

        while (current != nullptr) {
            if (current->edge->to == to) {
                if (prev == nullptr) {
                    adjLists[from->number].head = current->next;
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

    void EDIT_V(const char& name, const bool& newVisited) const noexcept {
        bool success = false;
        for (size_t i = 0; i != NV; ++i) {
            if (vertices[i].name == name) {
                vertices[i].visited = newVisited;
                return;
            }
        }

        if (!success) std::cout << "EDIT_V: Vertex " << name << " was not found!\n";
    }

    void EDIT_E(const char& vName, const char& wName, const float& newCost) const noexcept {
        Vertex* from = findVertexByName(vName);
        Vertex* to = findVertexByName(wName);

        if (from == nullptr) {
            std::cout << "EDIT_E: Vertex " << vName << " was not found!\n";
            return;
        }

        if (to == nullptr) {
            std::cout << "EDIT_E: Vertex " << wName << " was not found!\n";
            return;
        }

        if (from->name == '-' || to->name == '-') {
            std::cout << "ADD_E: One of the vertices [" << vName 
            << ", " << wName << "] is deleted!\n";
        }

        AdjNode* current = adjLists[from->number].head;
        while (current != nullptr) {
            if (current->edge->to == to) current->edge->cost = newCost;
            current = current->next;
        }
    }

    size_t FIRST(const char& name) const noexcept {
        Vertex* from = findVertexByName(name);
        if (from == nullptr) {
            std::cout << "FIRST: Vertex " << name << " was not found!\n";
            return UNREAL_VALUE;
        }

        AdjNode* current = adjLists[from->number].head;
        while (current != nullptr && current->edge->to->visited) {
            current = current->next;
        }

        if (current == nullptr) return UNREAL_VALUE;

        return current->edge->to->number;
    }

    size_t NEXT(const char& name, const size_t& i) const noexcept {
        Vertex* from = findVertexByName(name);
        if (from == nullptr) {
            std::cout << "NEXT: Vertex " << name << " was not found!\n";
            return UNREAL_VALUE;
        }

        AdjNode* current = adjLists[from->number].head;
        while (current != nullptr) {
            if (current->edge->to->number == i) {
                current = current->next;
                while (current != nullptr && current->edge->to->visited) {
                    current = current->next;
                }

                if (current == nullptr) return UNREAL_VALUE;
                return current->edge->to->number;
            }
            
            current = current->next;
        }

        return UNREAL_VALUE;
    }

    Vertex* VERTEX(const char& name, const size_t& i) const noexcept {
        Vertex* from = findVertexByName(name);
        if (from == nullptr) {
            std::cout << "VERTEX: Vertex " << name << " was not found!\n";
            return nullptr;
        }

        AdjNode* current = adjLists[from->number].head;
        while (current != nullptr) {
            if (current->edge->to->number == i) return current->edge->to;
            current = current->next;
        }

        return nullptr;
    }

    void DFS_START() const noexcept {
        if (countVertices == 0) {
            return;
        }

        size_t* path = new size_t[NV];
        float currentCost = 0.0f;
        size_t pathLength = 0;

        for (size_t i = 0; i != NV; ++i) {
            if (!vertices[i].visited) {
                DFS(i, path, pathLength, currentCost);
            }
        }

        delete[] path;
    }

    void setLength(const float& x) {
        length = x;
    }
};