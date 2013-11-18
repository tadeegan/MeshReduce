#include "triangle.h"
#include "vertex.h"

Triangle::Triangle(Vertex *v0,Vertex *v1,Vertex *v2){
    assert(v0!=v1 && v1!=v2 && v2!=v0);
    vertex[0]=v0;
    vertex[1]=v1;
    vertex[2]=v2;
    ComputeNormal();
    triangles.Add(this);
    for(int i=0;i<3;i++) {
        vertex[i]->face.Add(this);
        for(int j=0;j<3;j++) if(i!=j) {
            vertex[i]->neighbor.AddUnique(vertex[j]);
        }
    }
}
Triangle::~Triangle(){
    int i;
    triangles.Remove(this);
    for(i=0;i<3;i++) {
        if(vertex[i]) vertex[i]->face.Remove(this);
    }
    for(i=0;i<3;i++) {
        int i2 = (i+1)%3;
        if(!vertex[i] || !vertex[i2]) continue;
        vertex[i ]->RemoveIfNonNeighbor(vertex[i2]);
        vertex[i2]->RemoveIfNonNeighbor(vertex[i ]);
    }
}
int Triangle::HasVertex(Vertex *v) {
    return (v==vertex[0] ||v==vertex[1] || v==vertex[2]);
}
void Triangle::ComputeNormal(){
    Vector v0=vertex[0]->position;
    Vector v1=vertex[1]->position;
    Vector v2=vertex[2]->position;
    normal = (v1-v0)*(v2-v1);
    if(magnitude(normal)==0)return;
    normal = normalize(normal);
}
void Triangle::ReplaceVertex(Vertex *vold,Vertex *vnew) {
    assert(vold && vnew);
    assert(vold==vertex[0] || vold==vertex[1] || vold==vertex[2]);
    assert(vnew!=vertex[0] && vnew!=vertex[1] && vnew!=vertex[2]);
    if(vold==vertex[0]){
        vertex[0]=vnew;
    }
    else if(vold==vertex[1]){
        vertex[1]=vnew;
    }
    else {
        assert(vold==vertex[2]);
        vertex[2]=vnew;
    }
    int i;
    vold->face.Remove(this);
    assert(!vnew->face.Contains(this));
    vnew->face.Add(this);
    for(i=0;i<3;i++) {
        vold->RemoveIfNonNeighbor(vertex[i]);
        vertex[i]->RemoveIfNonNeighbor(vold);
    }
    for(i=0;i<3;i++) {
        assert(vertex[i]->face.Contains(this)==1);
        for(int j=0;j<3;j++) if(i!=j) {
            vertex[i]->neighbor.AddUnique(vertex[j]);
        }
    }
    ComputeNormal();
}
