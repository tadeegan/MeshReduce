#include "Vertex.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <List>
#include <string>

using namespace std;


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
Vec3 * validateAndCreateVertex(vector<string> strings){
    if(strings.size() != 4){
        cout << "invalid vertex size!" << endl;
        return NULL;
    }
    float _x = ::atof(strings[0].c_str());
    float _y = ::atof(strings[0].c_str());
    float _z = ::atof(strings[0].c_str());

    Vec3 * temp = new Vec3(_x, _y, _z);
    return temp;
}

int main () {
    std::cout << "decimating file" << std::endl;
    list<Vertex *> vertices;
    list<Triangle *> triangles;
    string line;
    ifstream myfile ("bunny.obj");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //std::cout << line << std::endl;
            if(line[0] == 'f'){
                ector<string> stringSplits;
                splitString(line, stringSplits, ' ');
            }
            else if(line[0] == 'v'){
                vector<string> stringSplits;
                splitString(line, stringSplits, ' ');
                Vec3 * temp = validateAndCreateVertex(stringSplits);
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
