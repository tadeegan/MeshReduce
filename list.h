/*
 *  Fairly typical of the list example you would 
 *  find in any c++ book.
 */
#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H


#include <assert.h>
#include <stdio.h>

class Vertex;
class Triangle;

template <typename Type>
class List {
    public:
       Type * element;
        int num;
        int array_size;
        Type &operator[](int i){assert(i>=0 && i<num); return element[i];}
        List(int s){
            num=0;
            array_size = 0;
            element = NULL;
            if(s) {
                allocate(s);
            }
        }

        List(){
            /*
            if (element != NULL) {
                delete element;
            }
            */
        }

        void allocate(int s){
            assert(s>0);
            assert(s>=num);
            Type *old = element;
            array_size =s;
            element = new Type[array_size];
            assert(element);
            for(int i=0;i<num;i++){
                element[i]=old[i];
            }
            //if(old) delete old;
        }

        void SetSize(int s){
            if(s==0) { if(element) delete element;}
            else {  allocate(s); }
            num=s;
        }
        void Pack(){
            allocate(num);
        }

        void Add(Type t){
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

        int Contains(Type t){
            int i;
            int count=0;
            for(i=0;i<num;i++) {
                if(element[i] == t) count++;
            }
            return count;
        }

            void AddUnique(Type t){
                if(!Contains(t)) Add(t);
            }


        void DelIndex(int i){
            assert(i<num);
            num--;
            while(i<num){
                element[i] = element[i+1];
                i++;
            }
        }

        void Remove(Type t){
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

        /**

          template <typename Type>
          void declarations() {
          List<Vertex *> vertexList;
          List<Triangle *> triangleList;
          }
          */
};

#endif
