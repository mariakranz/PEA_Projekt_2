//
// Created by Szef on 25.11.2023.
//

#include <climits>
#include "TSPGraph.h"

TSPGraph::TSPGraph(int verticesNumber, int **&adjacencyMatrix) {
    this->verticesNumber = verticesNumber;
    this->adjacencyMatrix = adjacencyMatrix;
}

TSPGraph::TSPGraph(int verticesNumber) {
    this->verticesNumber = verticesNumber;
    adjacencyMatrix = new int * [verticesNumber];                 //tworzenie macierzy sasiedztwa o odpowiednim rozmiarze
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int [verticesNumber];
        adjacencyMatrix[i][i] = INT_MAX;                    //wypełnianie wartosci po przekatnej jako nieskonczonosc
    }
}

TSPGraph::TSPGraph() {
    verticesNumber = 0;
    adjacencyMatrix = nullptr;
}



TSPGraph::~TSPGraph() {
    if (adjacencyMatrix != nullptr) {
        for (int i = 0; i < verticesNumber; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
}

int TSPGraph::addEdgeCost(int tail, int head, int cost) {
    if (head == tail) {
        return -1;
    }
    adjacencyMatrix[tail][head] = cost;
    return 0;
}

int **TSPGraph::getAdjMatrix() {
    return adjacencyMatrix;
}

int TSPGraph::getVerticesNumber(){
    return verticesNumber;
}

//double* TSPGraph::tabuSearch() {
////    double* initialSolution = new double [verticesNumber];
////    double initialCost = 0;
////    for(int i = 0; i < verticesNumber; i++){
////        initialSolution[i] = i;
////        if(i == verticesNumber-1) {
////            initialCost += adjacencyMatrix[i][0];
////        }else{
////            initialCost += adjacencyMatrix[i][i+1];
////        }
////    }
////
////    double* bestSolution = initialSolution;
////
////    return bestSolution;
//
//}



