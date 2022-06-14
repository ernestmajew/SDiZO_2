#include "Path.h"

Path::Path(){}

Path::~Path(){
    delete[] this->nodes;
    delete[] this->costs;

    this->totalCost = 0;
    this->size = 0;
}

void Path::addFront(size_t node, size_t cost){
    if(this->size == 0){
        totalCost = cost;

        this->nodes = new size_t;
        this->nodes[0] = node;

        this->costs = new size_t;
        this->costs[0] = cost;

        this->size++;

        return;
    }

    // zwiekszenie kosztu sciezki
    totalCost += cost;

    //Realokacja pamieci
    auto tempNodes = new size_t[this->size + 1];
    auto tempCosts = new size_t[this->size + 1];
    tempNodes[0] = node;
    tempCosts[0] = cost;
    for(int i = 1; i < this->size + 1; i++){
        tempNodes[i] = nodes[i - 1];
        tempCosts[i] = costs[i - 1];
    }
    delete[] this->nodes;
    delete[] this->costs;
    this->nodes = tempNodes;
    this->costs = tempCosts;
    this->size++;
}

void Path::displayPath(){
    if(this->size == 0){
        std::cout << "\nSciezka nie istnieje!\n";
        return;
    }

    std::cout << "Sciezka z " << nodes[0] << " do " << nodes[this->size - 1] << std::endl;
    std::cout << "(" << nodes[0] << " : " << costs[0] << ")";

    for(int i = 1; i < this->size; i++)
    {
        std::cout << "  ->  (" << nodes[i] << " : " << costs[i] << ")";
    }

    std::cout << "\nKoszt calkowity = " << totalCost << std::endl;
}