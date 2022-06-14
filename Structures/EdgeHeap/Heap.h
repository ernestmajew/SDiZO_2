#ifndef SDIZO_2_HEAP_H
#define SDIZO_2_HEAP_H

#include <stdexcept>
#include "../AdjacencyList/AdjacencyList.h"


class Heap {

    Edge** array;
    int size;

    void heapify(int i);

public:
    Heap();
    ~Heap();

    Edge* operator[](int);

    void push(Edge* edge);
    Edge* pop();

    void buildHeap();
    int getSize(){return this->size;}

};


#endif
