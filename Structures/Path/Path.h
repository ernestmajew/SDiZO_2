#ifndef SDIZO_2_PATH_H
#define SDIZO_2_PATH_H

#include <cstdlib>
#include <iostream>

class Path {

    size_t *nodes = nullptr;
    size_t *costs = nullptr;

    size_t totalCost = 0;

    size_t size = 0;

public:

    Path();
    ~Path();

    void addFront(size_t node, size_t cost);
    void displayPath();
};


#endif
