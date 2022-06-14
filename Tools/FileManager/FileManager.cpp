
#include "FileManager.h"

FileManager::FileManager(std::string filename){
    this->resultsPath = "../Files/" + filename;
    this->resultsFile.open(this->resultsPath.c_str(), std::fstream::out | std::fstream::trunc);
    this->resultsFile.seekp(0);
    this->resultsFile.clear();

    if(resultsFile.good())
    {
        this->resultsFile << "vertices;" << "density;" << "time;" << std::endl;
        this->resultsFile.flush();
    }
}

FileManager::FileManager(){
}

FileManager::~FileManager(){
    this->graphFile.close();

    delete[] this->table;

    this->edgesNumber = 0;
    this->nodesNumber = 0;
}

void FileManager::readFromFile(){
    std::cout << "Podaj nazwe pliku: \n";
    std::cin >> this->graphPath;
    this->graphFile.open(this->graphPath.c_str(), std::fstream::in);

    this->graphFile.clear();
    this->graphFile.seekg(0);

    if(this->graphFile.good()){
        this->graphFile >> this->nodesNumber >> this->edgesNumber;
        this->table =  new size_t [this->edgesNumber * 3];

        // Wpisanie danych
        for(int i = 0; i < this->edgesNumber * 3; i++){
            this->graphFile >> this->table[i];
        }
    }
}

void FileManager::writeToFile(size_t nodeCount, size_t density_, double time_)
{
    if(this->resultsFile.good()){
        this->resultsFile << nodeCount << ";" << density_ << ";" << time_ << ";" << std::endl;
        this->resultsFile.flush();
    }
}