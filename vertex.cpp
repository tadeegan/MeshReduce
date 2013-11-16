#include "vertex.h"
#include <iostream>


Vertex::Vertex(){
    this->position = Vec3(0,0,0);
}
Vertex::Vertex(float x, float y, float z, int _id){
    id = _id;
    position = Vec3(x, y, z);
}
Vertex::~Vertex(){
    //do something.... maybe?
}

void Vertex::RemoveIfNonNeighbor(Vertex *n){
    std::cout << "RemoveIfNonNeighbor" << std::endl;
    return;
}