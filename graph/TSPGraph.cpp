//
// Created by Szef on 25.11.2023.
//

#include <climits>
#include "TSPGraph.h"

TSPGraph::TSPGraph(int verticesNumber) {
    this->verticesNumber = verticesNumber;
    adjacencyMatrix = new double * [verticesNumber];                 //tworzenie macierzy sasiedztwa o odpowiednim rozmiarze
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new double [verticesNumber];
        adjacencyMatrix[i][i] = (double)INT_MAX;                    //wypełnianie wartosci po przekatnej jako nieskonczonosc
    }
}

//TSPGraph::TSPGraph() {
//    verticesNumber = 0;
//    adjacencyMatrix = new
//}

TSPGraph::~TSPGraph() {
    if (adjacencyMatrix != nullptr) {
        for (int i = 0; i < verticesNumber; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
}

int TSPGraph::addEdgeCost(int tail, int head, double cost) {
    if (head == tail) {
        return -1;
    }
    adjacencyMatrix[tail][head] = cost;
    return 0;
}

double **TSPGraph::getAdjMatrix() {
    return adjacencyMatrix;
}

int TSPGraph::getVerticesNumber() const {
    return verticesNumber;
}

int TSPGraph::addVerticle(int verticle) {
    return 0;
}

//int TSPGraph::loadDataFromFile(const char *filePath) {
//    return 0;
//}



