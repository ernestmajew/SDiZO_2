#ifndef SDIZO_2_ADJACENCYLIST_H
#define SDIZO_2_ADJACENCYLIST_H

#include <cstddef>
#include <iostream>
#include "../Graph.h"

struct Edge{    //Struktura zawierająca dane krawedzi
    Edge(const size_t &source_, const size_t &destination_, int cost_);

    int cost;
    size_t source;
    size_t destination;

    Edge* next = nullptr;
    Edge* previous = nullptr;
};

class AdjacencyList : public Graph {
    Edge **edgeArray;

public:
    AdjacencyList(const size_t& nodeCount, const size_t& edgeCount, const size_t* data);
    AdjacencyList(const size_t& nodesNumber_, const size_t& edgesNumber_);
    ~AdjacencyList();

    void addEdge(const size_t& source_, const size_t& destination_, const size_t& cost_);
    void displayGraph() override;

    size_t getNodesNumber() override;
    size_t getEdgesNumber() override;
    size_t getDensity() override;

    Edge** getEdgeTable();
};


#endif
