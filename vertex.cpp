#include "vertex.h"
#include "triangle.h"

Vertex::Vertex(Vector v,int _id) {
    position =v;
    id=_id;
    vertices.Add(this);
}

Vertex::~Vertex(){
    assert(face.num==0);
    while(neighbor.num) {
        neighbor[0]->neighbor.Remove(this);
        neighbor.Remove(neighbor[0]);
    }
    vertices.Remove(this);
}
void Vertex::RemoveIfNonNeighbor(Vertex *n) {
    // removes n from neighbor list if n isn't a neighbor.
    if(!neighbor.Contains(n)) return;
    for(int i=0;i<face.num;i++) {
        if(face[i]->HasVertex(n)) return;
    }
    neighbor.Remove(n);
}
