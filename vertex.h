#pragma once
#include "edge.h"

struct Vertex {
    char name; // название узла
    size_t number; // номер узла
    bool visited; // был ли посещён

    Vertex(const char& name, const size_t& number) : 
        name(name), number(number), visited(false) {}
    
    Vertex() : name(' '), number(size_t(-1)), visited(false) {}

    void setVisited() noexcept {
        visited = true;
    }

    void operator = (const Vertex& v) {
        name = v.name;
        number = v.number;
        visited = v.visited;
    }

    bool operator == (const Vertex* v) const noexcept {
        return this->name == v->name && this->number == v->number;
    }
};

class VertexIterator {
private:
    Vertex* vertices;
    size_t index, count;

public:
    VertexIterator(Vertex* v, const size_t& c, const size_t& start = 0) : 
        vertices(v), index(start), count(c) {
        moveToValid();
    }

    void moveToValid() {
        while (index < count && vertices[index].name == '-') {
            ++index;
        }
    }

    VertexIterator& operator ++ () noexcept {
        ++index;
        moveToValid();
        return *this;
    }

    Vertex& operator*() const noexcept {
        return vertices[index];
    }

    bool operator != (const VertexIterator& other) const {
        return index != other.index;
    }

    static VertexIterator begin(Vertex* vertices, size_t count) noexcept {
        return VertexIterator(vertices, count);
    }

    static VertexIterator end(Vertex* vertices, size_t count) noexcept {
        return VertexIterator(vertices, count, count);
    }
};