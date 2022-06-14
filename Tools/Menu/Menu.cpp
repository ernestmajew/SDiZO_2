#include "Menu.h"

Menu::Menu(){
    fm = new FileManager();
    test = new Tests();
}

void Menu::run() {
    std::cout << "[1] Minimalnie drzewo spinajace\n"
                 "[2] Najkrotsza sciezka w grafie\n"
                 "[3] Testy\n";

    int choice = -1;
    while (choice != 1 && choice != 2 && choice != 3) {
        std::cin >> choice;
    }

    switch (choice) {
        case 1:
            MSTmenu(false);
            run();
            break;
        case 2:
            pathMenu(false);
            run();
            break;
        case 3:
            test->allTests();
            std::cout << "\nTesty wykonano pomyslnie. Wyniki znajduja sie w plikach.\n\n";
            run();
            break;
    }
}

void Menu::MSTmenu(bool graphExist){
    int choice = -1;
    size_t nodes, density, source;

    std::cout << "[1] Generuj graf losowo\n"
                 "[2] Wczytaj graf z pliku.\n"
                 "[3] Wyswietl graf.\n"
                 "[4] Prim.\n"
                 "[5] Kruskal.\n"
                 "[6] Poprzenie menu\n";

    while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) {
        std::cin >> choice;
    }

    switch(choice){
        case 1:
            std::cout << "\nPodaj liczbe wierzcholkow: ";
            std::cin >> nodes;
            std::cout << "Podaj gestosc grafu: ";
            std::cin >> density;

            generator = new GraphGenerator(nodes, density);

            if(matrix != nullptr || list != nullptr){
                delete matrix;
                delete list;
            }

            matrix = new IncidenceMatrix(generator->getNodesNumber(), generator->getEdgesNumber(), generator->getData());
            list = new AdjacencyList(generator->getNodesNumber(), generator->getEdgesNumber(), generator->getData());
            std::cout << "\nWygenerowano graf\n\n";
            MSTmenu(true);
            break;

        case 2:
            fm->readFromFile();

            if(matrix != nullptr || list != nullptr){
                delete matrix;
                delete list;
            }

            matrix = new IncidenceMatrix(fm->getNodesNumber(), fm->getEdgesNumber(), fm->getData());
            list = new AdjacencyList(fm->getNodesNumber(), fm->getEdgesNumber(), fm->getData());
            MSTmenu(true);
            break;

        case 3:
            if(graphExist == 0){
                std::cout << "\nW pamieci nie ma zaladowanego grafu\n";
                MSTmenu(graphExist);
                break;
            }

            matrix->displayGraph();
            list->displayGraph();

            MSTmenu(graphExist);
            break;

        case 4:
            if(graphExist == 0){
                std::cout << "\nW pamieci nie ma zaladowanego grafu\n";
                MSTmenu(graphExist);
                break;
            }

            std::cout << "Podaj wierzcholek poczatkowy: " << std::endl;
            std::cin >> source;
            if (matrixResult != nullptr || listResult != nullptr) {
                delete matrixResult;
                delete listResult;
            }

            matrixResult = Prim::MST(matrix, source);
            matrixResult->displayGraph();

            listResult = Prim::MST(list, source);
            listResult->displayGraph();

            MSTmenu(graphExist);
            break;

        case 5:
            if(graphExist == 0){
                std::cout << "\nW pamieci nie ma zaladowanego grafu\n";
                MSTmenu(graphExist);
                break;
            }

            std::cout << "Podaj wierzcholek poczatkowy: " << std::endl;
            std::cin >> source;
            if(matrixResult != nullptr || listResult != nullptr)
            {
            delete matrixResult;
                delete listResult;
            }

            matrixResult = Kruskal::generateMST(matrix);
            matrixResult->displayGraph();

            listResult = Kruskal::generateMST(list);
            listResult->displayGraph();

            MSTmenu(graphExist);
            break;

        case 6:
            return;
    }
}

void Menu::pathMenu(bool graphExist){
    int choice = -1;
    size_t nodes, density, source, destination;

    std::cout << "[1] Generuj graf losowo\n"
                 "[2] Wczytaj graf z pliku.\n"
                 "[3] Wyswietl graf.\n"
                 "[4] Dijkstra.\n"
                 "[5] Bellman - Ford.\n"
                 "[6] Wyjscie\n";

    while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) {
        std::cin >> choice;
    }

    switch(choice){
        case 1:
            std::cout << "\nPodaj liczbe wierzcholkow: ";
            std::cin >> nodes;
            std::cout << "Podaj gestosc grafu: ";
            std::cin >> density;

            generator = new GraphGenerator(nodes, density);

            if(matrix != nullptr || list != nullptr){
                delete matrix;
                delete list;
            }

            matrix = new IncidenceMatrix(generator->getNodesNumber(), generator->getEdgesNumber(), generator->getData());
            list = new AdjacencyList(generator->getNodesNumber(), generator->getEdgesNumber(), generator->getData());
            std::cout << "\nWygenerowano graf\n\n";
            pathMenu(true);
            break;

        case 2:
            fm->readFromFile();

            if(matrix != nullptr || list != nullptr){
                delete matrix;
                delete list;
            }

            matrix = new IncidenceMatrix(fm->getNodesNumber(), fm->getEdgesNumber(), fm->getData());
            list = new AdjacencyList(fm->getNodesNumber(), fm->getEdgesNumber(), fm->getData());
            pathMenu(true);
            break;

        case 3:
            if(graphExist == 0){
                std::cout << "\nW pamieci nie ma zaladowanego grafu\n";
                pathMenu(graphExist);
                break;
            }

            matrix->displayGraph();
            list->displayGraph();
            pathMenu(graphExist);

            break;

        case 4:
            if(graphExist == 0){
                std::cout << "\nW pamieci nie ma zaladowanego grafu\n";
                pathMenu(graphExist);
                break;
            }

            std::cout << "\nPodaj wierzcholek startowy: ";
            std::cin >> source;
            std::cout << "\nPodaj wierzcholek koncowy: ";
            std::cin >> destination;


            std::cout << "\nMacierz\n";
            path = Dijkstra::findShortestPath(matrix, source, destination);
            path->displayPath();



            std::cout << "\nLista\n" << std::endl;
            path = Dijkstra::findShortestPath(list, source, destination);
            path->displayPath();

            pathMenu(graphExist);
            break;

        case 5:
            if(graphExist == 0){
                std::cout << "\nW pamieci nie ma zaladowanego grafu\n";
                pathMenu(graphExist);
                break;
            }

            std::cout << "\nPodaj wierzcholek startowy: ";
            std::cin >> source;
            std::cout << "\nPodaj wierzcholek koncowy: ";
            std::cin >> destination;

            std::cout << "\nMacierz\n";
            path = BellmanFord::findShortestPath(matrix, source, destination);
            path->displayPath();



            std::cout << "\nLista\n" << std::endl;
            path = BellmanFord::findShortestPath(list, source, destination);
            path->displayPath();

            pathMenu(graphExist);
            break;

        case 6:
            run();
            break;
    }
}
