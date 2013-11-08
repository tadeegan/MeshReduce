class Vertex {
    public:
        Vector position; // location of this point
        int id; // place of vertex in original list
        List<Vertex *> neighbor; // adjacent vertices
        List<Triangle *> face; // adjacent triangles
        float cost; // cached cost of collapsing edge
        Vertex * collapse; // candidate vertex for collapse
        Vertex(Vector v,int _id);
        ~Vertex();
        void RemoveIfNonNeighbor(Vertex *n);
};