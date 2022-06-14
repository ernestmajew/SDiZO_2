#ifndef SDIZO_2_GRAPHGENERATOR_H
#define SDIZO_2_GRAPHGENERATOR_H


#include <cstdlib>

class GraphGenerator {

    size_t nodeCount;
    size_t edgeCount;
    size_t density;

    size_t * data = nullptr;

    size_t size = 0;

public:

    GraphGenerator(size_t nodesNumber_, size_t density);
    ~GraphGenerator();

    size_t getNodesNumber(){return this->nodeCount;}
    size_t getEdgesNumber(){return this->edgeCount;}
    size_t* getData(){return this->data;}
};


#endif
