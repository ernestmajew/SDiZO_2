#ifndef SDIZO_2_GRAPH_H
#define SDIZO_2_GRAPH_H


#include <cstdlib>

class Graph {

protected:

    size_t nodeCount;
    size_t edgeCount;
    size_t density;

public:

    virtual void displayGraph() = 0;

    virtual size_t getNodesNumber() = 0;
    virtual size_t getEdgesNumber() = 0;
    virtual size_t getDensity() = 0;

};

#endif
