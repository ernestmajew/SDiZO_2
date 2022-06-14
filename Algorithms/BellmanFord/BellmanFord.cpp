#include "BellmanFord.h"
Path* BellmanFord::findShortestPath(IncidenceMatrix *incidenceMatrix, int src, int dest){
    auto nodeCount = incidenceMatrix->getNodesNumber();
    auto edgeCount = incidenceMatrix->getEdgesNumber()+1;
    auto matrix = incidenceMatrix->getMatrix();
    auto edgeValues = incidenceMatrix->getEdgesValues();

    auto distanceArray = new size_t [nodeCount];
    auto predecesorArray = new int [nodeCount];
    bool hasChanged = false;

    //Ustawienie tablel na wartosci startowe
    for(int i = 0; i < nodeCount; i++){
        distanceArray[i] = INT_MAX;
        predecesorArray[i] = -1;
    }
    distanceArray[src] = 0;

    //V-1 razy wykonujemy relaksacje kazdej z krawedzi
    for(int i = 0; i < nodeCount - 1; i++){
        for(int source = 0; source < nodeCount; source++){
            if(distanceArray[source] == INT_MAX)
                continue;

            for(int edge = 0; edge < edgeCount; edge++){
                if (matrix[source][edge] != -1)
                    continue;

                for(int destination = 0; destination < edgeCount; destination++){
                    if(matrix[destination][edge] != 1)
                        continue;

                    if (distanceArray[destination] > distanceArray[source] + edgeValues[edge]){
                        distanceArray[destination] = distanceArray[source] + edgeValues[edge];
                        predecesorArray[destination] = source;

                        hasChanged = true;
                    }
                    break;
                }

            }
        }

        //Dodatkowy waunek stopu. Jesli nie dokonano zadnej relaksacji zakoncz dzialanie
        if(!hasChanged)
            break;
    }


    //Utworzenie sciezki wynikowej
    auto resultPath = new Path();
    auto currentIndex = dest;
    auto tempPrevious = predecesorArray[currentIndex];

    do{
        if(currentIndex == src){ resultPath->addFront(currentIndex, 0); break; }
        if(distanceArray[currentIndex] == INT_MAX) break;

        resultPath->addFront(currentIndex, distanceArray[currentIndex] - distanceArray[tempPrevious]);

        currentIndex = tempPrevious;
        tempPrevious = predecesorArray[currentIndex];

    }while(currentIndex != -1);

    return resultPath;
}

Path* BellmanFord::findShortestPath(AdjacencyList *list, int src, int dest){
    auto nodeCount = list->getNodesNumber();
    auto edgeArray = list->getEdgeTable();

    auto distances = new size_t [nodeCount];
    auto previous = new int [nodeCount];
    bool hasChanged = false;

    for(int i = 0; i < nodeCount; i++)
    {
        distances[i] = INT_MAX;
        previous[i] = -1;
    }
    distances[src] = 0;

    for(int i = 0; i < nodeCount - 1; i++){
        for(int j = 0; j < nodeCount; j++){
            if(distances[j] == INT_MAX)
                continue;

            auto tempEdge = edgeArray[j];

            while (tempEdge != nullptr){
                if (distances[tempEdge->destination] > distances[tempEdge->source] + tempEdge->cost) {
                    distances[tempEdge->destination] = distances[tempEdge->source] + tempEdge->cost;
                    previous[tempEdge->destination] = tempEdge->source;

                    hasChanged = true;
                }

                if (tempEdge->next != nullptr) tempEdge = tempEdge->next;
                else break;
            }

            if (!hasChanged)
                break;
        }
    }

    auto resultPath = new Path();
    auto currentIndex = dest;
    auto tempPrevious = previous[currentIndex];

    do{
        if(currentIndex == src){ resultPath->addFront(currentIndex, 0); break; }
        if(distances[currentIndex] == INT_MAX) break;

        resultPath->addFront(currentIndex, distances[currentIndex] - distances[tempPrevious]);

        currentIndex = tempPrevious;
        tempPrevious = previous[currentIndex];

    }while(currentIndex != -1);

    return resultPath;
}