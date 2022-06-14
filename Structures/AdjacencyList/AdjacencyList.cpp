#include "AdjacencyList.h"

Edge::Edge(const size_t &source_, const size_t &destination_, int cost_)
    : source(source_), destination(destination_), cost(cost_){}


AdjacencyList::AdjacencyList(const size_t& nodeCount, const size_t& edgeCount, const size_t* data){
    this->nodeCount = nodeCount;
    this->edgeCount = edgeCount;

    // wypelnienie listy nullptr
    this->edgeArray = new Edge * [this->nodeCount]{nullptr};

    // Dodawanie krawedzi
    for(int dataIndex = 0; dataIndex < this->edgeCount * 3;){
        auto tempEdge = new Edge(data[dataIndex], data[dataIndex + 1], data[dataIndex + 2]);

        // sprawdzenie czy pierwszy wskaznik jest pusty
        if(this->edgeArray[data[dataIndex]] == nullptr) this->edgeArray[data[dataIndex]] = tempEdge;
        else{
            auto tempPointer = this->edgeArray[data[dataIndex]];
            // przejscie po kazdym elemencie listy
            while(tempPointer->next != nullptr){ tempPointer = tempPointer->next; }
            tempPointer->next = tempEdge;
            tempEdge->previous = tempPointer;
        }
        dataIndex += 3;
    }
    // obliczanie gestosci
    this->density = ((2 * this->edgeCount * 100) / (this->nodeCount * (this->nodeCount - 1)));

}

AdjacencyList::AdjacencyList(const size_t& nodesNumber_, const size_t& edgesNumber_){
    this->nodeCount = nodesNumber_;
    this->edgeCount = edgesNumber_;
    this->edgeArray = new Edge * [this->nodeCount]{nullptr};
}

AdjacencyList::~AdjacencyList(){
    for(int i = 0; i < this->nodeCount; i++){
        auto tempPointer = this->edgeArray[i];

        if(tempPointer == nullptr)
            continue;

        while(tempPointer->next != nullptr){
            tempPointer = tempPointer->next;
            delete tempPointer->previous;
        }
        delete tempPointer;
    }

    delete[] this->edgeArray;

    this->nodeCount = 0;
    this->edgeCount = 0;
}

void AdjacencyList::addEdge(const size_t& source_, const size_t& destination_, const size_t& cost_){
    auto edge = new Edge(source_, destination_, cost_);

    // Sprawdzenie czy pierwszy wskaznik jest pusty
    if(this->edgeArray[edge->source] == nullptr) edgeArray[edge->source] = edge;
    else{
        auto tempPointer = this->edgeArray[edge->source];
        while(tempPointer->next != nullptr){ tempPointer = tempPointer->next; }
        tempPointer->next = edge;
        edge->previous = tempPointer;
    }
}

void AdjacencyList::displayGraph() {
    std::cout<<"\n(cel : koszt)\n";
    for (int i = 0; i < nodeCount; i++){
        auto tempPointer = edgeArray[i];
        std::cout << i << " - ";
        while(tempPointer != nullptr){
            std::cout << "(" << tempPointer->destination << " : " << tempPointer->cost << ") ";
            tempPointer = tempPointer->next;
        }
        std::cout << "\n";
    }
}

size_t AdjacencyList::getNodesNumber(){return this->nodeCount;}
size_t AdjacencyList::getEdgesNumber(){return this->edgeCount;}
size_t AdjacencyList::getDensity(){return this->density;}
Edge** AdjacencyList::getEdgeTable(){return this->edgeArray;}