#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"
#include "vec3.h"
#include <vector>
using std::vector;

class Vertex;

class Triangle {
    public:
        Vertex * verts[3];// the 3 points that make this tri
        Vec3 normal; // orthogonal unit vector
        Triangle(Vertex *v0,Vertex *v1,Vertex *v2);
        ~Triangle();
        void ComputeNormal();
        void ReplaceVertex(Vertex *vold,Vertex *vnew);
        int HasVertex(Vertex *v);
};

#endif