#ifndef SDIZO_2_MENU_H
#define SDIZO_2_MENU_H

#include "../Tests/Tests.h"

class Menu {

    FileManager *fm = nullptr;
    Tests *test = nullptr;

    GraphGenerator *generator = nullptr;

    IncidenceMatrix *matrix = nullptr;
    IncidenceMatrix *matrixResult = nullptr;

    AdjacencyList *list = nullptr;
    AdjacencyList *listResult = nullptr;

    Path *path = nullptr;

    void MSTmenu(bool graphExist);
    void pathMenu(bool graphExist);

public:
    Menu();

    void run();
};

#endif
