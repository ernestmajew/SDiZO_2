#include "Dijkstra.h"

Path* Dijkstra::findShortestPath(IncidenceMatrix *incidenceMatrix, int src, int dst){
    auto nodeCount = incidenceMatrix->getNodesNumber();
    auto edgeCount = incidenceMatrix->getEdgesNumber();
    auto matrix = incidenceMatrix->getMatrix();
    auto edgeValues =  incidenceMatrix->getEdgesValues();
    auto heap = new Heap();

    auto distanceArray = new size_t [nodeCount];
    auto predecesorArray = new int [nodeCount];
    auto visitedNodes = new bool [nodeCount];
    auto nodesToRelax = new bool [nodeCount];

    // Ustawienie startowych wartosci
    for(int i = 0; i < nodeCount; i++){
        distanceArray[i] = INT_MAX;
        predecesorArray[i] = -1;
        visitedNodes[i] = false;
        nodesToRelax[i] = true;
    }

    auto addEdges = [&](int src){
        for(int i = 0; i < edgeCount; i++){
            size_t source, destination;

            if(matrix[src][i] == -1){
                source = src;
                for(int j = 0; j < nodeCount; j++)
                    if(matrix[j][i] == 1){
                        destination = j;
                        break;
                    }
                heap->push(new Edge(source, destination, edgeValues[i]));
            }
        }
    };

    distanceArray[src] = 0;
    visitedNodes[src] = true;
    nodesToRelax[src] = false;
    int currentNode = src;

    Edge *currentEdge = nullptr;

    addEdges(src);
    while(isEmpty(visitedNodes, nodeCount)){
        if(heap->getSize() != 0){
            currentEdge = heap->pop();

            // Relaksacja
            if(distanceArray[currentEdge->destination] > distanceArray[currentEdge->source] + currentEdge->cost){
                distanceArray[currentEdge->destination] = distanceArray[currentEdge->source] + currentEdge->cost;
                predecesorArray[currentEdge->destination] = currentEdge->source;
            }
            continue;
        }

        nodesToRelax[currentNode] = false;
        visitedNodes[currentNode] = true;

        // Sprawdzenie kolejnego wierzcholka
        currentNode = getMin(distanceArray, visitedNodes, nodesToRelax, nodeCount);
        if(currentNode == -1)break;

        // Dodanie do kolejki krawedzi z nowego wierzcholka
        addEdges(currentNode);
    }

    //Tworzenie sciezki wynikowej
    auto resultPath = new Path();
    auto currentIndex = dst;
    auto tempPrevious = predecesorArray[currentIndex];

    do{
        if(currentIndex == src){ resultPath->addFront(currentIndex, 0); break; }
        if(distanceArray[currentIndex] == INT_MAX) break;

        resultPath->addFront(currentIndex, distanceArray[currentIndex] - distanceArray[tempPrevious]);

        currentIndex = tempPrevious;
        tempPrevious = predecesorArray[currentIndex];

    }while(currentIndex != -1);

    currentEdge = nullptr;
    delete heap;
    delete[] predecesorArray;
    delete[] distanceArray;
    delete[] nodesToRelax;

    return resultPath;
}

Path* Dijkstra::findShortestPath(AdjacencyList *list, int src, int dst){
    auto nodeCount = list->getNodesNumber();
    auto edgeArray = list->getEdgeTable();
    auto heap = new Heap();
    auto distanceArray = new size_t [nodeCount];
    auto predecesorArray = new int [nodeCount];
    auto visitedNodes = new bool [nodeCount];
    auto nodesToRelax = new bool [nodeCount];

    // Ustawienie wartosci poczatkowych
    for(int i = 0; i < nodeCount; i++)
    {
        distanceArray[i] = INT_MAX;
        predecesorArray[i] = -1;
        visitedNodes[i] = false;
        nodesToRelax[i] = true;
    }


    auto addEdges = [&](int src){
        auto tempEdge = edgeArray[src];
        while(tempEdge != nullptr){
            heap->push(tempEdge);
            tempEdge = tempEdge->next;
        }
    };

    addEdges(src);
    distanceArray[src] = 0;
    visitedNodes[src] = true;
    nodesToRelax[src] = false;
    int currentNode = src;

    Edge *currentEdge = nullptr;

    while(isEmpty(visitedNodes, nodeCount)){
        if(heap->getSize() != 0){
            currentEdge = heap->pop();

            // Relaksacja
            if(distanceArray[currentEdge->destination] > distanceArray[currentEdge->source] + currentEdge->cost){
                distanceArray[currentEdge->destination] = distanceArray[currentEdge->source] + currentEdge->cost;
                predecesorArray[currentEdge->destination] = currentEdge->source;
            }
            continue;
        }

        nodesToRelax[currentNode] = false;
        visitedNodes[currentNode] = true;

        // Ustawienie następnego wierzcholka
        currentNode = getMin(distanceArray, visitedNodes, nodesToRelax, nodeCount);

        // Warunek stopu
        if(currentNode == -1) break;

        // Dodanie krawedzi nastepnego wierzcholka
        addEdges(currentNode);
    }

    auto resultPath = new Path();
    auto currentIndex = dst;
    auto tempPrevious = predecesorArray[currentIndex];

    // Tworzenie sciezki wynikowej
    do{
        if(currentIndex == src){resultPath->addFront(currentIndex, 0);break;}
        if(distanceArray[currentIndex] == INT_MAX)break;

        resultPath->addFront(currentIndex, distanceArray[currentIndex] - distanceArray[tempPrevious]);
        currentIndex = tempPrevious;
        tempPrevious = predecesorArray[currentIndex];

    }while(currentIndex != -1);

    currentEdge = nullptr;
    delete heap;
    delete[] predecesorArray;
    delete[] distanceArray;
    delete[] nodesToRelax;

    return resultPath;
}

bool Dijkstra::isEmpty(bool *table, size_t size){
    for(int i = 0; i < size; i++)
        if(!table[i])
            return true;
    return false;
}

int Dijkstra::getMin(size_t *table, bool* visited, bool *toRelax, size_t size){
    int min = INT_MAX;
    int index =  -1;

    for(int i = 0; i < size; i++){
        if(table[i] < min && !visited[i] && toRelax[i]){
            index = i;
            min = table[i];
        }
    }
    return index;
}