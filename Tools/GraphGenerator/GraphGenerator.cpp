#include <cmath>
#include "GraphGenerator.h"

GraphGenerator::GraphGenerator(size_t nodesNumber_, size_t density_)
    : nodeCount(nodesNumber_), density(density_){
    this->edgeCount = (this->density) * this->nodeCount * (this->nodeCount - 1) / 200;
    int edgesToCreate = this->edgeCount;
    this->data = new size_t[this->edgeCount * 3];
    for(int i = 0; i < this->edgeCount * 3; i++){
        data[i] = INT_MAX;
    }

    // Tworzenie grafu spojnego
    for(int i = 0; i < this->nodeCount; i++){
        if(i == this->nodeCount - 1){
            data[i * 3] = i;
            data[i * 3 + 1] = 0;
            data[i * 3 + 2] = rand() % 100;
        }
        else{
            data[i * 3] = i;
            data[i * 3 + 1] = i + 1;
            data[i * 3 + 2] = rand() % 100;
        }

        this->size += 3;
        edgesToCreate--;
    }

    // Tworzenie pozostałych krawedzi (Jesli trzeba)
    while(edgesToCreate != 0){
        bool exists = false;
        int source = rand() % this->nodeCount;
        int destination = rand() % this->nodeCount;
        int cost = rand() % 100;

        while(source == destination){
            destination = rand() % this->nodeCount;
        }

        for(int i = 0; data[i] != INT_MAX; i += 3){
            if(data[i] == source && data[i + 1] == destination || data[i] == destination && data[i + 1] == source){
                exists = true;
                break;
            }
        }

        // Dodanie krawedzi jesli jeszcze nie istnieje
        if(!exists){
            data[this->size] = source;
            data[this->size + 1] = destination;
            data[this->size + 2] = cost;

            this->size += 3;
            edgesToCreate--;
        }
    }
}

GraphGenerator::~GraphGenerator(){
    delete[] this->data;

    this->nodeCount = 0;
    this->edgeCount = 0;
    this->density = 0;
}