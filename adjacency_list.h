#pragma once
#include "vertex.h"
#include "edge.h"

struct AdjNode {
    Edge* edge; // дуга (там находятся данные о двух вершинах и стоимости дуги)
    AdjNode* next; // следующий элемент смежности

    AdjNode(Edge* e) :
        edge(e), next(nullptr) {}

    ~AdjNode() {
        delete edge;
    }
};

struct AdjList {
    AdjNode* head; // главный элемент

    AdjList() : head(nullptr) {}

    ~AdjList() {
        AdjNode* current = head;
        while (current != nullptr) {
            AdjNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};