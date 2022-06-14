#ifndef SDIZO_2_KRUSKAL_H
#define SDIZO_2_KRUSKAL_H

#include "../../Structures/IncidenceMatrix/IncidenceMatrix.h"
#include "../../Structures/EdgeHeap/Heap.h"
#include "../../Structures/AdjacencyList/AdjacencyList.h"

class Kruskal {
public:

    static IncidenceMatrix* generateMST(IncidenceMatrix* incidenceMatrix);
    static AdjacencyList* generateMST(AdjacencyList* list);
};


#endif
