#include "vertex.h"
#include "triangle.h"
#include "vector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>   

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

    int num_traingles = num_verts - 2;
    for(int i = 0; i < num_traingles; i++){
        std::cout << line << std::endl;
        std::cout << "making triangle: " << indicies[0] << " " << indicies[1+i] << " " << indicies[2+i] << std::endl;
        Triangle * temp = new Triangle(vertices[indicies[0]], vertices[indicies[1+i]], vertices[indicies[2+i]]);
        triangles.Add(temp);
    }
}

int main () {
    int numVerts = 1;

    std::cout << "decimating file" << std::endl;
 
    std::string line;
    std::ifstream myfile ("bunny.obj");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //std::std::cout << line << std::std::endl;
            if(line[0] == 'f'){
                parsePolyLine(line);
            }
            else if(line[0] == 'v'){
                std::vector<std::string> stringSplits;
                splitString(line, stringSplits, ' ');
                Vertex * temp = validateAndCreateVertex(stringSplits, numVerts);
                numVerts++;
                vertices.Add(temp);
            }
        }
        myfile.close();
    }
    else{
        std::cout << "Unable to open file"; 
    }
    //reduce

    return 0;
}
