#include "IncidenceMatrix.h"

IncidenceMatrix::IncidenceMatrix(const size_t & nodeCount, const size_t &edgeCount, const size_t *data){
    this->nodeCount = nodeCount;
    this->edgeCount = edgeCount;
    this->matrix = new int *[nodeCount];

    // Wypelnienie macierzy zerami
    for (int i = 0; i < nodeCount; i++) {
        matrix[i] = new int[edgeCount];
        for (int j = 0; j < edgeCount; j++)
            matrix[i][j] = 0;
    }


    this->edgesValues = new int[edgeCount];
    int dataIndex = 0;
    int edgeValueIndex = 0;

    // Wpisanie do macierzy krawedzi
    for (int i = 0; i < edgeCount; i++) {
        this->matrix[data[dataIndex]][i] = -1;
        dataIndex++;
        this->matrix[data[dataIndex]][i] = 1;
        dataIndex++;
        this->edgesValues[edgeValueIndex] = data[dataIndex];

        dataIndex++;
        edgeValueIndex++;
    }
    this->density = ((2 * this->edgeCount * 100) / (this->nodeCount * (this->nodeCount - 1)));
}

IncidenceMatrix::IncidenceMatrix(const size_t & nodeCount, const size_t &edgeCount){
    this->nodeCount = nodeCount;
    this->edgeCount = edgeCount;
    matrix = new int*[this->nodeCount];

    // wypelnienie macierzy zerami
    for(int i = 0; i < this->nodeCount; i++){
        this->matrix[i] = new int [this->edgeCount];

        for(int j = 0; j < this->edgeCount; j++)
            this->matrix[i][j] = 0;
    }

    this->edgesValues = new int [this->edgeCount]{-1};
    this->density = ((2 * this->edgeCount * 100) / (this->nodeCount * (this->nodeCount - 1)));
}

IncidenceMatrix::~IncidenceMatrix(){
    if(this->matrix != nullptr){
        for(int i = 0; i < this->nodeCount; i++){
            delete[] this->matrix[i];
        }
        delete[] this->matrix;
        delete[] this->edgesValues;

        edgeCount = 0;
        nodeCount = 0;
    }
}

void IncidenceMatrix::addEdge(const size_t &source, const size_t &destination, const size_t &cost){
    // wpisanie krawedzi do macierzy
    this->matrix[source][this->usedEdges] = -1;
    this->matrix[destination][this->usedEdges] = 1;
    this->edgesValues[this->usedEdges] = cost;

    // zwiekszenie liczbby krawedzi
    this->usedEdges++;
}

void IncidenceMatrix::displayGraph()
{
    std::cout << "  E   ";
    for (size_t i = 0; i < this->edgeCount; i++){std::cout << i << "      ";}
    std::cout << "\nV\n";

    for (size_t i = 0; i < this->nodeCount; i++){
        std::cout << i << "    ";
        for (size_t j = 0; j < this->edgeCount; j++){
            std::cout << std::setw(2) << int(this->matrix[i][j]) << "  |  ";
        }
        std::cout << "\n";
    }

    std::cout << "\nv    ";

    for (size_t i = 0; i < this->edgeCount; i++){
        std::cout << std::setw(2) << this->edgesValues[i] << "  |  ";
    }

    std::cout <<"\n";
}

size_t IncidenceMatrix::getNodesNumber(){return this->nodeCount;}
size_t IncidenceMatrix::getEdgesNumber(){return this->edgeCount;}
size_t IncidenceMatrix::getDensity(){return this->density;}
int** IncidenceMatrix::getMatrix(){return this->matrix;}
int* IncidenceMatrix::getEdgesValues(){return this->edgesValues;}