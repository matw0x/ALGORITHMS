#pragma once
#include "edge.h"

struct Vertex {
    char name; // название узла
    size_t number; // номер узла
    bool visited; // был ли посещён

    Vertex(const char& name, const size_t& number) : 
        name(name), number(number), visited(false) {}
    
    Vertex() : name(' '), number(size_t(-1)), visited(false) {}

    bool isVisited() const noexcept {
        return visited == true;
    }

    void setVisited() noexcept {
        visited = true;
    }

    void operator = (const Vertex& v) {
        name = v.name;
        number = v.number;
        visited = v.visited;
    }

    bool operator == (const Vertex* v) {
        return this->name == v->name && this->number == v->number;
    }
};