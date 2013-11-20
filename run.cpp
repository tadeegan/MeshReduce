#include "vertex.h"
#include "triangle.h"
#include "vector.h"
#include "progmesh.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>   

List<Vertex *> vertices(0);
List<Triangle *> triangles(0);
List<Vector> vert;
List<tridata> tri;

unsigned int splitString(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    int in_string_bool = 0;
    size_t start_pos = 0;
    size_t it_pos = 0;
    strs.clear();
    // Decompose statement
    while( it_pos < txt.length()) {
        if(in_string_bool && txt[it_pos] == ch && it_pos > start_pos){
            //end of word
            strs.push_back( txt.substr( start_pos, it_pos - start_pos) );
            in_string_bool = 0;
        }
        if(!in_string_bool && txt[it_pos] != ch){
            in_string_bool = 1;
            start_pos = it_pos;
        }
        it_pos++;
    }
    // Add the last one
    if(in_string_bool && it_pos > start_pos){
        strs.push_back( txt.substr( start_pos, it_pos - start_pos) );
    }
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
    std::vector<std::string> spaceSplits;
    splitString(line, spaceSplits, ' ');
    std::vector<std::string> rep;
    std::vector <std::vector <std::string> > slashSplits(spaceSplits.size(), rep);
    for(int i = 0; i < spaceSplits.size(); i++){
        splitString(spaceSplits[i], slashSplits[i], '/');
    }
    int num_verts = slashSplits.size() - 1;
    int indicies[num_verts];
    for(int i=1; i < num_verts + 1; i++){
        indicies[i-1] = atoi(slashSplits[i][0].c_str()) - 1;
    }

    int num_triangles = num_verts - 2;
    for(int i = 0; i < num_triangles; i++){
        tridata td;
    	td.v[0]=indicies[0];
    	td.v[1]=indicies[1+i];
    	td.v[2]=indicies[2+i];
        //std::cout << td.v[0] << " " << td.v[1] << " " << td.v[2] << std::endl;

    	tri.Add(td);
    }
}

void parseVertice(const std::string & line) {
    std::vector<std::string> parsed;
    splitString(line, parsed, ' ');
    if(parsed.size() != 4){
        std::cout << "error parsing vert: " << line << std::endl;
    }
    double double_x = ::atof(parsed[1].c_str());
    double double_y = ::atof(parsed[2].c_str());
    double double_z = ::atof(parsed[3].c_str());
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

int main (int argc, char* argv[]) {
    if(argc < 3 || argc > 4){
        printf("Usage: exe <filename> <decimation percent>\n");
        exit(0);
    }
    float percent = atof(argv[2]);
    int numVerts = 1;

    std::cout << "decimating file" << std::endl;

    int currByte = 0;
    struct stat filestatus;
    stat( argv[1], &filestatus );
    int numBytes = filestatus.st_size;
    std::string line;
    std::ifstream myfile (argv[1]);

    if (myfile.is_open())
    {
        
        while ( getline (myfile,line) )
        {
            //std::std::cout << line << std::std::endl;
            if(line[0] == 'v' && (line[1] == 'n' || line[1] == 't')){

            }
            else if(line[0] == 'f'){
                parsePolyLine(line);
            }
            else if(line[0] == 'v'){
                parseVertice(line);
            }
            currByte = currByte + line.length();
            printf ("\r%f%% parsing", 100.0*(float)currByte/(float)numBytes);
            fflush (stdout);
        }
        printf ("\r%f%% parsing .. done\n", 100.0f);

        myfile.close();
    }
    else{
        std::cout << "Unable to open file"; 
    }
    List<int> permutation;
    List<int> mm;
    
    //std::cout << "before vert num: " << vert.num << std::endl;
    ProgressiveMesh(vert, tri, mm, permutation, percent);
    return 0;
}
