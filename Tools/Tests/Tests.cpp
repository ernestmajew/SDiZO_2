#include "Tests.h"

Tests::Tests(){
    this->timer = new Timer();
}

Tests::~Tests(){
    delete this->timer;
}

void Tests::Prim() {
    auto listFile = new FileManager("prim-list-results.csv");
    auto matrixFile = new FileManager("prim-matrix-results.csv");
    double listTime = 0, matrixTime = 0;
    int src;

    for (int density = 0; density < 4; density++) {
        for (int nodeCount = 0; nodeCount < 5; nodeCount++) {
            listTime = 0, matrixTime = 0;
            for (int repeatCount = 0; repeatCount < 100; repeatCount++) {

                this->generator = new GraphGenerator(nodesNumber[nodeCount], densities[density]);
                this->testList = new AdjacencyList(this->generator->getNodesNumber(),this->generator->getEdgesNumber(), this->generator->getData());
                this->testMatrix = new IncidenceMatrix(this->generator->getNodesNumber(),this->generator->getEdgesNumber(), this->generator->getData());


                src = rand() % nodesNumber[nodeCount];

                this->timer->startTimer();
                Prim::MST(this->testMatrix, src);
                matrixTime += (int)(10000*timer->stopTimer());

                this->timer->startTimer();
                Prim::MST(this->testList, src);
                listTime += (int)(10000*timer->stopTimer());

                delete this->generator;
                delete this->testList;
            }
            matrixTime /= (double) 10000;
            listTime /= (double) 10000;

            listFile->writeToFile(nodesNumber[nodeCount], densities[density], listTime);
            matrixFile->writeToFile(nodesNumber[nodeCount], densities[density], matrixTime);
        }
    }
}

void Tests::Kruskal() {
    auto listFile = new FileManager("kruskal-list-results.csv");
    auto matrixFile = new FileManager("kruskal-matrix-results.csv");
    double listTime = 0, matrixTime = 0;

    for (int density = 0; density < 4; density++) {
        for (int nodeCount = 0; nodeCount < 5; nodeCount++) {
            listTime = 0, matrixTime = 0;
            for (int repeatCount = 0; repeatCount < 100; repeatCount++) {

                this->generator = new GraphGenerator(nodesNumber[nodeCount], densities[density]);
                this->testList = new AdjacencyList(this->generator->getNodesNumber(),this->generator->getEdgesNumber(), this->generator->getData());
                this->testMatrix = new IncidenceMatrix(this->generator->getNodesNumber(),this->generator->getEdgesNumber(), this->generator->getData());

                this->timer->startTimer();
                Kruskal::generateMST(this->testList);
                listTime += (int)(10000*timer->stopTimer());

                this->timer->startTimer();
                Kruskal::generateMST(this->testMatrix);
                matrixTime += (int)(10000*timer->stopTimer());

                delete this->generator;
                delete this->testList;

            }
            matrixTime /= (double) 10000;
            listTime /= (double) 10000;

            listFile->writeToFile(nodesNumber[nodeCount], densities[density], listTime);
            matrixFile->writeToFile(nodesNumber[nodeCount], densities[density], matrixTime);
        }
    }
}

void Tests::BellmanFord(){
    auto listFile = new FileManager("bellman-ford-list-results.csv");
    auto matrixFile = new FileManager("bellman-ford-matrix-results.csv");
    double listTime = 0, matrixTime = 0;

    for(int density = 0; density < 4; density++) {
        for (int nodeCount = 0; nodeCount < 5; nodeCount++) {
            for (int repeatCount = 0; repeatCount < 100; repeatCount++) {

                this->generator = new GraphGenerator(nodesNumber[nodeCount], densities[density]);
                this->testList = new AdjacencyList(this->generator->getNodesNumber(),
                                                   this->generator->getEdgesNumber(), this->generator->getData());
                this->testMatrix = new IncidenceMatrix(this->generator->getNodesNumber(),
                                                       this->generator->getEdgesNumber(), this->generator->getData());

                int source = rand() % nodesNumber[nodeCount];
                int destination = rand() % nodesNumber[nodeCount];

                while(source == destination)
                {
                    destination = rand() % nodesNumber[nodeCount];
                }

                this->timer->startTimer();
                BellmanFord::findShortestPath(this->testList, source, destination);
                listTime += (int)(10000*timer->stopTimer());

                this->timer->startTimer();
                BellmanFord::findShortestPath(this->testList, source, destination);
                matrixTime += (int)(10000*timer->stopTimer());

                delete this->generator;
                delete this->testList;
                delete this->returnPath;
            }

            listTime /= (double)10000;
            matrixTime /= (double)10000;

            listFile->writeToFile(nodesNumber[nodeCount], densities[density], listTime);
            matrixFile->writeToFile(nodesNumber[nodeCount], densities[density], matrixTime);
        }
    }
}

void Tests::Dijkstra(){
    auto listFile = new FileManager("dijkstra-list-results.csv");
    auto matrixFile = new FileManager("dijkstra-matrix-results.csv");
    double listTime = 0, matrixTime = 0;

    for(int density = 0; density < 4; density++) {
        for (int nodeCount = 0; nodeCount < 5; nodeCount++) {
            for (int repeatCount = 0; repeatCount < 100; repeatCount++) {

                this->generator = new GraphGenerator(nodesNumber[nodeCount], densities[density]);
                this->testList = new AdjacencyList(this->generator->getNodesNumber(),
                                                   this->generator->getEdgesNumber(), this->generator->getData());
                this->testMatrix = new IncidenceMatrix(this->generator->getNodesNumber(),
                                                       this->generator->getEdgesNumber(), this->generator->getData());

                int source = rand() % nodesNumber[nodeCount];
                int destination = rand() % nodesNumber[nodeCount];

                while(source == destination)
                {
                    destination = rand() % nodesNumber[nodeCount];
                }

                this->timer->startTimer();
                Dijkstra::findShortestPath(this->testList, source, destination);
                listTime += (int)(10000*timer->stopTimer());

                this->timer->startTimer();
                Dijkstra::findShortestPath(this->testList, source, destination);
                matrixTime += (int)(10000*timer->stopTimer());

                delete this->generator;
                delete this->testList;
                delete this->returnPath;
            }

            listTime /= (double)10000;
            matrixTime /= (double)10000;

            listFile->writeToFile(nodesNumber[nodeCount], densities[density], listTime);
            matrixFile->writeToFile(nodesNumber[nodeCount], densities[density], matrixTime);
        }
    }
}

void Tests::allTests(){
    Prim();
    Kruskal();
    Dijkstra();
    BellmanFord();
}
