#include "progmesh.h"
#include <iostream>

float ComputeEdgeCollapseCost(Vertex *u,Vertex *v) {

    int i;
    float edgelength = magnitude(v->position - u->position);
    float curvature=0;

    // find the "sides" triangles that are on the edge uv
    List<Triangle *> sides;
    for(i=0;i<u->face.num;i++) {
        if(u->face[i]->HasVertex(v)){
            sides.Add(u->face[i]);
        }
    }
    // use the triangle facing most away from the sides 
    // to determine our curvature term
    for(i=0;i<u->face.num;i++) {
        float mincurv=1; // curve for face i and closer side to it
        for(int j=0;j<sides.num;j++) {
            // use dot product of face normals. '^' defined in vector
            float dotprod = u->face[i]->normal ^ sides[j]->normal;
            mincurv = std::min(mincurv,(1-dotprod)/2.0f);
        }
        curvature = std::max(curvature,mincurv);
    }
    // the more coplanar the lower the curvature term   
    return edgelength * curvature;
}

void ComputeEdgeCostAtVertex(Vertex *v) {
    // compute the edge collapse cost for all edges that start
    // from vertex v.  Since we are only interested in reducing
    // the object by selecting the min cost edge at each step, we
    // only cache the cost of the least cost edge at this vertex
    // (in member variable collapse) as well as the value of the 
    // cost (in member variable objdist).
    if(v->neighbor.num==0) {
        // v doesn't have neighbors so it costs nothing to collapse
        v->collapse=NULL;
        v->objdist=-0.01f;
        return;
    }
    v->objdist = 1000000;
    v->collapse=NULL;
    // search all neighboring edges for "least cost" edge
    for(int i=0;i<v->neighbor.num;i++) {
        float dist;
        dist = ComputeEdgeCollapseCost(v,v->neighbor[i]);
        if(dist<v->objdist) {
            v->collapse=v->neighbor[i];  // candidate for edge collapse
            v->objdist=dist;             // cost of the collapse
        }
    }
}
void ComputeAllEdgeCollapseCosts() {
    // For all the edges, compute the difference it would make
    // to the model if it was collapsed.  The least of these
    // per vertex is cached in each vertex object.
    for(int i=0;i<vertices.num;i++) {
        ComputeEdgeCostAtVertex(vertices[i]);
    }
}

void Collapse(Vertex *u,Vertex *v){
    // Collapse the edge uv by moving vertex u onto v
    // Actually remove tris on uv, then update tris that
    // have u to have v, and then remove u.
    if(!v) {
        // u is a vertex all by itself so just delete it
        delete u;
        return;
    }
    int i;
    List<Vertex *>tmp;
    // make tmp a list of all the neighbors of u
    for(i=0;i<u->neighbor.num;i++) {
        tmp.Add(u->neighbor[i]);
    }
    // delete triangles on edge uv:
    for(i=u->face.num-1;i>=0;i--) {
        if(u->face[i]->HasVertex(v)) {
            delete(u->face[i]);
        }
    }
    // update remaining triangles to have v instead of u
    for(i=u->face.num-1;i>=0;i--) {
        u->face[i]->ReplaceVertex(u,v);
    }
    delete u; 
    // recompute the edge collapse costs for neighboring vertices
    for(i=0;i<tmp.num;i++) {
        ComputeEdgeCostAtVertex(tmp[i]);
    }
}

void AddVertex(List<Vector> &vert){
    for(int i=0;i<vert.num;i++) {
        Vertex *v = new Vertex(vert[i],i);
    }
}
void AddFaces(List<tridata> &tri){
    for(int i=0;i<tri.num;i++) {
        Triangle *t=new Triangle(
                          vertices[tri[i].v[0]],
                          vertices[tri[i].v[1]],
                          vertices[tri[i].v[2]] );
    }
}

Vertex *MinimumCostEdge(){
    // Find the edge that when collapsed will affect model the least.
    // This funtion actually returns a Vertex, the second vertex
    // of the edge (collapse candidate) is stored in the vertex data.
    // Serious optimization opportunity here: this function currently
    // does a sequential search through an unsorted list :-(
    // Our algorithm could be O(n*lg(n)) instead of O(n*n)
    Vertex *mn=vertices[0];
    for(int i=0;i<vertices.num;i++) {
        if(vertices[i]->objdist < mn->objdist) {
            mn = vertices[i];
        }
    }
    return mn;
}

void ProgressiveMesh(List<Vector> &vert, List<tridata> &tri, List<int> &map, List<int> &permutation , float percentage)
{
    AddVertex(vert);  // put input data into our data structures
    AddFaces(tri);
    ComputeAllEdgeCollapseCosts(); // cache all edge collapse costs
    permutation.SetSize(vertices.num);  // allocate space
    map.SetSize(vertices.num);          // allocate space
    // reduce the object down to nothing:
    int remaining = (int)((float)vertices.num * percentage);
    while(vertices.num > remaining) {
        // get the next vertex to collapse
        Vertex *mn = MinimumCostEdge();
        std::cout << "min cost edge: " << mn << " num left: " << vertices.num <<  std::endl;
        // keep track of this vertex, i.e. the collapse ordering
        permutation[mn->id]=vertices.num-1;
        // keep track of vertex to which we collapse to
        map[vertices.num-1] = (mn->collapse)?mn->collapse->id:-1;
        // Collapse this edge
        Collapse(mn,mn->collapse);
    }

    // reorder the map list based on the collapse ordering
    for(int i=0;i<map.num;i++) {
        map[i] = (map[i]==-1)?0:permutation[map[i]];
    }
    // The caller of this function should reorder their vertices
    // according to the returned "permutation".
}
