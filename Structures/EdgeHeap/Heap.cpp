#include "Heap.h"

Heap::Heap(){
    this->size = 0;
}

Heap::~Heap(){
    if(this->size == 0){
        this->array = nullptr;
        return;
    }

    delete[] this->array;
    this->array = nullptr;
    this->size = 0;
}

void Heap::heapify(int i){
    int min {i}, left {2*i + 1}, right {2*i + 2};

    if(left < this->size && array[left]->cost < array[min]->cost)min = left;
    if(right < this->size && array[right]->cost < array[min]->cost)min = right;
    if(min != i){
        std::swap(array[i], array[min]);
        heapify(min);
    }
}


Edge* Heap::operator[](int position){
    if(position < 0 || position >= this->size)
        throw new std::out_of_range("You are out of range");

    else
        return *(array + position);
}


void Heap::push(Edge* edge){
    if(this-> size == 0){
        this->size++;
        this->array = new Edge* [this->size];
        this->array[0] = edge;

        return;
    }
    this->size++;

    auto tempTable = new Edge * [this->size];

    // realokacja pamieci
    for(int i = 0; i < this->size - 1; i++){
        tempTable[i] = this->array[i];
    }

    // dodanie elementu
    tempTable[this->size - 1] = edge;

    // usuniecie poprzedniej tablicy
    delete[] this->array;
    this->array = tempTable;
    this->buildHeap();
}

Edge* Heap::pop(){
    if(this->size == 0)
        return nullptr;

    auto returnEdge = this->array[0];

    if(this->size == 1){
        this->size--;
        delete[] array;
        return returnEdge;
    }

    std::swap(this->array[0], this->array[this->size - 1]);
    this->size--;
    this->array[this->size] = nullptr;
    buildHeap();
    return returnEdge;
}

void Heap::buildHeap(){
    int startIndex {(this->size / 2) - 1};
    for(int i = startIndex; i >= 0; i--)
        heapify(i);
}