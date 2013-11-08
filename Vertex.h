#include <vector>
#include <List>

using std::vector;
using std::list;

class Vertex {
    public:
        vector<float> position; // location of this point
        int id; // place of vertex in original list
        List<Vertex *> neighbor; // adjacent vertices
        List<Triangle *> face; // adjacent triangles
        float cost; // cached cost of collapsing edge
        Vertex * collapse; // candidate vertex for collapse
        Vertex(vector * v,int _id);
        ~Vertex();
        void RemoveIfNonNeighbor(Vertex *n);
};