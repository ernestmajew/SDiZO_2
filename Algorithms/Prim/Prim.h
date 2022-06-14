#ifndef SDIZO_2_PRIM_H
#define SDIZO_2_PRIM_H

#include "../../Structures/IncidenceMatrix/IncidenceMatrix.h"
#include "../../Structures/EdgeHeap/Heap.h"
#include "../../Structures/AdjacencyList/AdjacencyList.h"

class Prim{
    static bool isEmpty(const bool* array, size_t size);

public:
    static IncidenceMatrix* MST(IncidenceMatrix* incidenceMatrix, int src);
    static AdjacencyList* MST(AdjacencyList* list, int src);
};
#endif
