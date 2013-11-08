#include "Vertex.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <List>
#include <string>

using namespace std::cout;
using namespace std::list;

int main () {
    list<Vertex *> vertices;
    list<Triangle *> triangles;
    string line;
    ifstream myfile ("bunny.obj");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << endl;
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    return 0;
}