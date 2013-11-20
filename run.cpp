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
List<Vector> vert;
List<tridata> tri;

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

void parsePolyLine(std::string line){
    std::vector<std::string> stringSplits;
    splitString(line, stringSplits, ' ');
    int num_verts = stringSplits.size() - 1;
    int indicies[num_verts];
    for(int i=1; i < num_verts + 1; i++){
        indicies[i-1] = atoi(stringSplits[i].c_str()) - 1;
    }

    int num_triangles = num_verts - 2;
    for(int i = 0; i < num_triangles; i++){
        //std::cout << line << std::endl;
        tridata td;
	td.v[0]=indicies[0];
	td.v[1]=indicies[1+i];
	td.v[2]=indicies[2+i];
	tri.Add(td);
    }
}

void parseVertice(const std::string & line) {
    int counter = 0;
    std::string x = "";
    std::string y = "";
    std::string z = "";
    for (int i = 1; i < line.length(); ++i) {
        if (line[i] == ' ') {
            ++counter;
            continue;
        }
        if (counter == 1) {
            x += line[i];
        }
        else if (counter == 2) {
            y += line[i];
        }
        else{
            z += line[i];
        }
    }
    double double_x = ::atof(x.c_str());
    double double_y = ::atof(y.c_str());
    double double_z = ::atof(z.c_str());
    vert.Add(Vector(double_x, double_y, double_z));
}

void PermuteVertices(List<int> &permutation) {
    // rearrange the vertex list 
    List<Vector> temp_list;
    int i;
    assert(permutation.num==vert.num);
    for(i=0;i<vert.num;i++) {
        temp_list.Add(vert[i]);
    }
    for(i=0;i<vert.num;i++) {
        vert[permutation[i]]=temp_list[i];
    }
    // update the changes in the entries in the triangle list
    for(i=0;i<tri.num;i++) {
        for(int j=0;j<3;j++) {
            tri[i].v[j] = permutation[tri[i].v[j]];
        }
    }
}

int main () {
    int numVerts = 1;

    //std::cout << "decimating file" << std::endl;

    std::string line;
    std::ifstream myfile ("models/box.obj");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //std::std::cout << line << std::std::endl;
            if(line[0] == 'f'){
                parsePolyLine(line);
            }
            else if(line[0] == 'v'){
                parseVertice(line);
            }
        }
        myfile.close();
    }
    else{
        std::cout << "Unable to open file"; 
    }
    List<int> permutation;
    List<int> mm;
    
    //std::cout << "before vert num: " << vert.num << std::endl;
    ProgressiveMesh(vert, tri, mm, permutation, 0.5f);
    //PermuteVertices(permutation);
    //std::cout << "vert num: " << vert.num << std::endl;
    //std::cout << "permutation num: " << permutation.num << std::endl;
    //std::cout << "mm num: " << mm.num << std::endl;

    return 0;
}
