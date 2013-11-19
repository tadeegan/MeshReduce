/*
#include "list.h"
//#include "triangle.h"
//#include "vertex.h"

template <typename Type>
List<Type>::List(int s){
    num=0;
    array_size = 0;
    element = NULL;
    if(s) {
        allocate(s);
    }
}

template <typename Type>
List<Type>::~List(){
    delete element;
}

template <typename Type>
void List<Type>::allocate(int s){
    assert(s>0);
    assert(s>=num);
    Type *old = element;
    array_size =s;
    element = new Type[array_size];
    assert(element);
    for(int i=0;i<num;i++){
        element[i]=old[i];
    }
    if(old) delete old;
}

template <typename Type>
void List<Type>::SetSize(int s){
    if(s==0) { if(element) delete element;}
    else {  allocate(s); }
    num=s;
}
template <typename Type>
void List<Type>::Pack(){
    allocate(num);
}

template <typename Type>
void List<Type>::Add(Type t){
    assert(num<=array_size);
    if(num==array_size) {
        allocate((array_size)?array_size *2:16);
    }
    //int i;
    //for(i=0;i<num;i++) {
        // dissallow duplicates
    //  assert(element[i] != t);
    //}
    element[num++] = t;
}

template <typename Type>
int List<Type>::Contains(Type t){
    int i;
    int count=0;
    for(i=0;i<num;i++) {
        if(element[i] == t) count++;
    }
    return count;
}

template <typename Type>
void List<Type>::AddUnique(Type t){
    if(!Contains(t)) Add(t);
}


template <typename Type>
void List<Type>::DelIndex(int i){
    assert(i<num);
    num--;
    while(i<num){
        element[i] = element[i+1];
        i++;
    }
}

template <typename Type>
void List<Type>::Remove(Type t){
    int i;
    for(i=0;i<num;i++) {
        if(element[i] == t) {
            break;
        }
    }
    DelIndex(i);
    for(i=0;i<num;i++) {
        assert(element[i] != t);
    }

}


 * This function instantiates vertain template types to avoid linker errors.

template <typename Type>
void List<Type>::declarations() {
    List<Vertex *> vertexList;
    List<Triangle *> triangleList;
}
*/

