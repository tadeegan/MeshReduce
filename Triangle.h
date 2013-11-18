#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"
#include "vector.h"


class Vertex;

class Triangle {
  public:
    Vertex *         vertex[3]; // the 3 points that make this tri
    Vector           normal;    // unit vector othogonal to this face
                     Triangle(Vertex *v0,Vertex *v1,Vertex *v2);
                     ~Triangle();
    void             ComputeNormal();
    void             ReplaceVertex(Vertex *vold,Vertex *vnew);
    int              HasVertex(Vertex *v);
};
#endif