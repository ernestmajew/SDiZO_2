#ifndef SDIZO_2_DIJKSTRA_H
#define SDIZO_2_DIJKSTRA_H

#include "../../Structures/EdgeHeap/Heap.h"
#include "../../Structures/IncidenceMatrix/IncidenceMatrix.h"
#include "../../Structures/Path/Path.h"
#include "../../Structures/AdjacencyList/AdjacencyList.h"

class Dijkstra{

    static bool isEmpty(bool *table, size_t size);
    static int getMin(size_t *table, bool* visited, bool *toRelax, size_t size);

public:

    static Path* findShortestPath(IncidenceMatrix *incidenceMatrix, int src, int dst);

    static Path* findShortestPath(AdjacencyList *list, int src, int dst);
};


#endif
