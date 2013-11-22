/*
 *  Fairly typical of the list example you would 
 *  find in any c++ book.
 */
#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H


#include <assert.h>
#include <stdio.h>
#include <iostream>

class Vertex;
class Triangle;

template <typename Type>
class List {
    public:
        Type * element;
        int num;
        int array_size; Type &operator[](int i);
        List(int s);
        List();

        void allocate(int s);
        void SetSize(int s);
        void Pack();
        void Add(Type t);
        int Contains(Type t);
        void AddUnique(Type t);
        void DelIndex(int i);
        void Remove(Type t);
        /**

          template <typename Type>
          void declarations() {
          List<Vertex *> vertexList;
          List<Triangle *> triangleList;
          }
          */
};

#include "list.cpp"

#endif
