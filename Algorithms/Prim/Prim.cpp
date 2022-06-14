#include "Prim.h"


IncidenceMatrix* Prim::MST(IncidenceMatrix* incidenceMatrix, int src){
    size_t edgeCount = incidenceMatrix->getEdgesNumber();
    size_t nodeCount = incidenceMatrix->getNodesNumber();
    auto matrix = incidenceMatrix->getMatrix();
    auto edgeValues = incidenceMatrix->getEdgesValues();
    size_t totalCost = 0;
    auto heap = new Heap();
    auto result = new IncidenceMatrix(nodeCount, edgeCount);
    auto visitedNodes = new bool[nodeCount]{false};
    visitedNodes[src] = true;

    //Funkcja dodawania do kopca krawedzi wychodzacych od wierzcholka
    auto addEdges = [&](int src){
        size_t source, destination;
        for(int i = 0; i < edgeCount; i++){
            if(matrix[src][i] != 0){
                for(int j = 0; j < nodeCount; j++){
                    if(matrix[j][i] == -1) source = j;
                    if(matrix[j][i] == 1) destination = j;
                }
                heap->push(new Edge(source, destination, edgeValues[i]));
            }
        }
    };

    //Dodanie krawedzi wychodzacych z wierzcholka startowego
    addEdges(src);

    while(isEmpty(visitedNodes, nodeCount)) {
        auto currentEdge = heap->pop();

        //Jesli odwiedzamy nowy wierzcholek to dodajemy krawedz do wyniku i dodajemy krawedzie wychodzace od nowego wierzcholka
        if(!visitedNodes[currentEdge->destination]){
            visitedNodes[currentEdge->destination] = true;
            totalCost += currentEdge->cost;
            result->addEdge(currentEdge->source, currentEdge->destination, currentEdge->cost);
            addEdges(currentEdge->destination);
        }

        if(!visitedNodes[currentEdge->source]){
            visitedNodes[currentEdge->source] = true;
            totalCost += currentEdge->cost;
            result->addEdge(currentEdge->source, currentEdge->destination, currentEdge->cost);
            addEdges(currentEdge->source);
        }
    }

    return result;
}

AdjacencyList* Prim::MST(AdjacencyList* list, int src){
    auto edgeCount = list->getEdgesNumber();
    auto nodeCount = list->getNodesNumber();
    auto edgeArray = list->getEdgeTable();
    auto heap = new Heap();
    auto visitedNodes = new bool[nodeCount]{false};
    visitedNodes[src] = true;
    int totalCost = 0;
    auto result = new AdjacencyList(nodeCount, edgeCount);
    Edge* tempPointer = nullptr;

    auto addEdges = [&](int src) {
        for (int i = 0; i < nodeCount; i++) {
            tempPointer = edgeArray[i];

            while (tempPointer != nullptr) {
                if (tempPointer->source == src || tempPointer->destination == src) {
                    heap->push(tempPointer);
                }
                tempPointer = tempPointer->next;
            }
        }
    };

    addEdges(src);
    while(isEmpty(visitedNodes, nodeCount)){
        auto currentEdge = heap->pop();

        if(!visitedNodes[currentEdge->destination]){
            totalCost += currentEdge->cost;
            visitedNodes[currentEdge->destination] = true;

            result->addEdge(currentEdge->source, currentEdge->destination, currentEdge->cost);
            addEdges(currentEdge->destination);
        }

        if(!visitedNodes[currentEdge->source]){
            totalCost += currentEdge->cost;
            visitedNodes[currentEdge->source] = true;

            result->addEdge(currentEdge->destination, currentEdge->source, currentEdge->cost);
            addEdges(currentEdge->source);
        }
    }

    delete tempPointer;
    delete[] visitedNodes;
    delete heap;

    return result;
}

bool Prim::isEmpty(const bool *array, size_t size){
    for(int i = 0; i < size; i++)
        if(!array[i])
            return true;
    return false;
}