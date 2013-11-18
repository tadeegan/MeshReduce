#include "Vertex.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <List>
#include <string>

using namespace std;

vector<Vertex *> vertices;
vector<Triangle *> triangles;

unsigned int splitString(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos + 1 ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
Vertex * validateAndCreateVertex(vector<string> strings){
    if(strings.size() != 4){
        cout << "invalid vertex size!" << endl;
        return NULL;
    }
    float _x = ::atof(strings[0].c_str());
    float _y = ::atof(strings[0].c_str());
    float _z = ::atof(strings[0].c_str());

    Vertex * v = new Vertex(_x, _y, _z, 1);
    return v;
}

void parsePolyLine(string line){
    vector<string> stringSplits;
    splitString(line, stringSplits, ' ');
    int num_verts = stringSplits.size() - 1;
    int indicies[num_verts];
    for(int i=1; i < num_verts + 1; i++){
        indicies[i-1] = atoi(stringSplits[i].c_str()) - 1;
    }

    int num_traingles = num_verts - 2;
    for(int i = 0; i < num_traingles; i++){
        cout << line << endl;
        cout << "making triangle: " << indicies[0] << " " << indicies[1+i] << " " << indicies[2+i] << endl;
        Triangle * temp = new Triangle(vertices[indicies[0]], vertices[indicies[1+i]], vertices[indicies[2+i]]);
        triangles.push_back(temp);
    }
}

int main () {
    std::cout << "decimating file" << std::endl;
 
    string line;
    ifstream myfile ("bunny.obj");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //std::cout << line << std::endl;
            if(line[0] == 'f'){
                parsePolyLine(line);
            }
            else if(line[0] == 'v'){
                vector<string> stringSplits;
                splitString(line, stringSplits, ' ');
                Vertex * temp = validateAndCreateVertex(stringSplits);
                vertices.push_back(temp);
            }
        }
        myfile.close();
    }
    else{
        std::cout << "Unable to open file"; 
    }

    return 0;
}
