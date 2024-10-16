#pragma once
#include "vertex.h"
#include "edge.h"

struct AdjNode {
    Edge* edge; // дуга (данные о двух вершинах и стоимости дуги)
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

class AdjListIterator {
private:
    AdjNode* current;
    
public:
    AdjListIterator(AdjNode* start) : current(start) {}

    AdjListIterator& operator ++ () noexcept {
        if (current != nullptr) current = current->next;
        return *this;
    }

    AdjNode* operator * () const noexcept {
        return current;
    }

    bool operator != (const AdjListIterator& other) const noexcept {
        return current != other.current;
    }

    static AdjListIterator begin(AdjNode* start) noexcept {
        return AdjListIterator(start);
    }

    static AdjListIterator end() noexcept {
        return AdjListIterator(nullptr);
    }
};