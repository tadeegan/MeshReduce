#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <List>
#include "triangle.h"
#include "vec3.h"

using std::vector;
using std::list;

class Triangle;

class Vertex {
    public:
        Vec3 position; // location of this point
        int id; // place of vertex in original list
        list<Vertex *> neighbor; // adjacent vertices
        list<Triangle *> face; // adjacent triangles
        float cost; // cached cost of collapsing edge
        Vertex * collapse; // candidate vertex for collapse
        Vertex();
        Vertex(float x, float y, float z ,int _id);
        ~Vertex();
        void RemoveIfNonNeighbor(Vertex *n);
        Vertex operator=(const Vertex & other);
    private:
        void _clear();
        void _copy();
};

#endif