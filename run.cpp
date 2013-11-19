#include "vertex.h"
#include "triangle.h"
#include "vector.h"
#include "progmesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>   

List<Vertex *> vertices(0);
List<Triangle *> triangles(0);

unsigned int splitString(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos + 1 ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
Vertex * validateAndCreateVertex(std::vector<std::string> strings, int id){
    if(strings.size() != 4){
        std::cout << "invalid vertex size!" << std::endl;
        return NULL;
    }
    float _x = ::atof(strings[0].c_str());
    float _y = ::atof(strings[0].c_str());
    float _z = ::atof(strings[0].c_str());
    Vector a(_x, _y, _z);
    Vertex * v = new Vertex(a, id);
    return v;
}

void parsePolyLine(std::string line, List<tridata> & triList){
    std::vector<std::string> stringSplits;
    splitString(line, stringSplits, ' ');
    int num_verts = stringSplits.size() - 1;
    int indicies[num_verts];
    for(int i=1; i < num_verts + 1; i++){
        indicies[i-1] = atoi(stringSplits[i].c_str()) - 1;
    }

    int num_triangles = num_verts - 2;
    for(int i = 0; i < num_triangles; i++){
        std::cout << line << std::endl;
        tridata td;
	td.v[0]=indicies[0];
	td.v[1]=indicies[1+i];
	td.v[2]=indicies[2+i];
	triList.Add(td);
    }
}

int main () {
    int numVerts = 1;

    std::cout << "decimating file" << std::endl;
 
    std::string line;
    std::ifstream myfile ("bunny.obj");
    List<Vector> vert;       // global list of vertices
    List<tridata> tri;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //std::std::cout << line << std::std::endl;
            if(line[0] == 'f'){
                parsePolyLine(line, tri);
            }
            else if(line[0] == 'v'){

            }
        }
        myfile.close();
    }
    else{
        std::cout << "Unable to open file"; 
    }
    List<int> permutation;
    List<int> mm;
    //ProgressiveMesh(vert, tri, mm, permutation); 
    //reduce

    return 0;
}
