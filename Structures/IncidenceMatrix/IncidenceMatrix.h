#ifndef SDIZO_2_INCIDENCEMATRIX_H
#define SDIZO_2_INCIDENCEMATRIX_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "../Graph.h"

class IncidenceMatrix : public Graph{

    size_t usedEdges = 0;

    int **matrix;
    int *edgesValues;

public:

    IncidenceMatrix(const size_t & nodeCount, const size_t &edgeCount, const size_t *data);
    IncidenceMatrix(const size_t & nodeCount, const size_t &edgeCount);
    ~IncidenceMatrix();

    void addEdge(const size_t &source, const size_t &destination, const size_t &cost);

    void displayGraph() override;

    size_t getNodesNumber() override;
    size_t getEdgesNumber() override;
    size_t getDensity() override;

    int** getMatrix();
    int* getEdgesValues();
};


#endif
