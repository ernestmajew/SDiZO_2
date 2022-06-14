#ifndef SDIZO_2_TESTS_H
#define SDIZO_2_TESTS_H

#include "../Timer/Timer.h"
#include "../FileManager/FileManager.h"
#include "../GraphGenerator/GraphGenerator.h"

#include "../../Structures/Graph.h"

#include "../../Algorithms/BellmanFord/BellmanFord.h"
#include "../../Algorithms/Dijsktra/Dijkstra.h"
#include "../../Algorithms/Kruskal/Kruskal.h"
#include "../../Algorithms/Prim/Prim.h"

class Tests {
    Timer *timer = nullptr;
    AdjacencyList *testList = nullptr;
    IncidenceMatrix *testMatrix = nullptr;
    Path *returnPath = nullptr;

    GraphGenerator *generator = nullptr;

    constexpr static const int densities[4] = {25, 50, 75, 99};
    constexpr static const int nodesNumber[5] = {20, 40, 60, 80, 100};

public:
    Tests();
    ~Tests();

    void Prim();
    void BellmanFord();
    void allTests();
    void Kruskal();
    void Dijkstra();
};
#endif
