#include <vector>
using std::vector;


class Triangle {
    public:
        Vertex * vertex[3];// the 3 points that make this tri
        vector normal; // orthogonal unit vector
        Triangle(Vertex *v0,Vertex *v1,Vertex *v2);
        ~Triangle();
        void ComputeNormal();
        void ReplaceVertex(Vertex *vold,Vertex *vnew);
        int HasVertex(Vertex *v);
};