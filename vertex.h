#ifndef VERTEX_H
#define VERTEX_H

#include "list.h"
#include "triangle.h"
#include "vector.h"

class Triangle;

class Vertex {
  public:
    Vector           position; // location of point in euclidean space
    int              id;       // place of vertex in original list
    List<Vertex *>   neighbor; // adjacent vertices
    List<Triangle *> face;     // adjacent triangles
    float            objdist;  // cached cost of collapsing edge
    Vertex *         collapse; // candidate vertex for collapse
                     Vertex(Vector v,int _id);
                     ~Vertex();
    void             RemoveIfNonNeighbor(Vertex *n);
};

#endif