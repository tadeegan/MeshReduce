#include "triangle.h"

Triangle::Triangle(Vertex *v0,Vertex *v1,Vertex *v2){
    verts[0] = v0;
    verts[1] = v1;
    verts[2] = v2;
}
Triangle::~Triangle(){
    //duno what to do here
}
void Triangle::ComputeNormal(){
    //I know how to do this!
}
void Triangle::ReplaceVertex(Vertex *vold,Vertex *vnew){
    //Replace verts
}
int Triangle::HasVertex(Vertex *v){
    return 1;
}