#pragma once
#include "vertex.h"

struct Vertex;

struct Edge {
    Vertex *from, *to; // откуда и куда
    float cost; // стоимость (вес) дуги

    Edge(Vertex* from, Vertex* to, const float& cost) :
        from(from), to(to), cost(cost) {}

    // ~Edge(); - по факту реализация описана в ~Graph()
};