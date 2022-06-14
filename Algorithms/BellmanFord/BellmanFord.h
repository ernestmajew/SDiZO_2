#ifndef SDIZO_2_BELLMANFORD_H
#define SDIZO_2_BELLMANFORD_H


#include "../../Structures/IncidenceMatrix/IncidenceMatrix.h"
#include "../../Structures/EdgeHeap/Heap.h"
#include "../../Structures/Path/Path.h"
#include "../../Structures/AdjacencyList/AdjacencyList.h"

class BellmanFord {
public:
    static Path* findShortestPath(IncidenceMatrix *incidenceMatrix, int src, int dest);
    static Path* findShortestPath(AdjacencyList *list, int src, int dest);

};


#endif
