#include "Kruskal.h"
#include "../../Structures/AdjacencyList/AdjacencyList.h"
IncidenceMatrix* Kruskal::generateMST(IncidenceMatrix* incidenceMatrix){
    auto edgeCount = incidenceMatrix->getEdgesNumber();
    auto nodeCount = incidenceMatrix->getNodesNumber();
    auto matrix = incidenceMatrix->getMatrix();
    auto edgeValues = incidenceMatrix->getEdgesValues();

    auto heap = new Heap();
    auto resultMatrix = new IncidenceMatrix(nodeCount, edgeCount);

    int totalCost = 0;
    int connectedEdges = 0;

    // Tablica na id zbiorów rozłącznych
    auto setsID = new size_t[nodeCount];

    for(int i = 0; i < nodeCount; i++){
        setsID[i] = i;
    }

    // Utworzenie kolejki krawedzi
    for(int i = 0; i < edgeCount; i++){
        size_t source, destination;

        for(int j = 0; j < nodeCount; j++){
            if(matrix[j][i] == -1)source = j;
            if(matrix[j][i] == 1)destination = j;
        }
        heap->push(new Edge(source, destination, edgeValues[i]));
    }

    while(heap->getSize()){
        if(connectedEdges == nodeCount - 1)break; //Warunek stopu. MST ma V-1 krawedzi

        auto minEdge = heap->pop();

        if(setsID[minEdge->source] != setsID[minEdge->destination]){ //Jesli krawedz nie tworzy cyklu dodajemy ja do macierzy wynikowej
            resultMatrix->addEdge(minEdge->source, minEdge->destination, minEdge->cost);

            auto oldID = setsID[minEdge->source];
            auto newID = setsID[minEdge->destination];

            for(int i = 0; i < nodeCount; i++){
                if(setsID[i] == oldID)
                    setsID[i] = newID;
            }
            totalCost += minEdge->cost;
            connectedEdges++;
        }
    }

    return resultMatrix;
}

AdjacencyList* Kruskal::generateMST(AdjacencyList* list){
    auto edgeCount = list->getEdgesNumber();
    auto nodeCount = list->getNodesNumber();
    auto edgeArray = list->getEdgeTable();

    auto heap = new Heap();
    auto listToReturn = new AdjacencyList(nodeCount, edgeCount);

    int totalCost = 0;
    int connectedEdges = 0;

    // Tablica na id zbiorów rozłącznych
    auto setsID = new size_t[nodeCount];

    for(int i = 0; i < nodeCount; i++){
        setsID[i] = i;
    }

    Edge* tempEdge = nullptr;

    for(int i = 0; i < nodeCount; i++){
        tempEdge = edgeArray[i];

        while(tempEdge != nullptr){
            heap->push(tempEdge);
            tempEdge = tempEdge->next;
        }
    }

    while(heap->getSize()){
        auto minEdge = heap->pop();

        if(connectedEdges == nodeCount - 1)break;

        if(setsID[minEdge->source] != setsID[minEdge->destination]){
            listToReturn->addEdge(minEdge->source, minEdge->destination, minEdge->cost);

            // łączenie zbiorów
            auto oldID = setsID[minEdge->source];
            auto newID = setsID[minEdge->destination];

            for(int i = 0; i < nodeCount; i++){
                if(setsID[i] == oldID)
                    setsID[i] = newID;
            }
            totalCost += minEdge->cost;
            connectedEdges++;
        }
    }

    tempEdge = nullptr;
    delete heap;
    delete[] setsID;

    return listToReturn;
}