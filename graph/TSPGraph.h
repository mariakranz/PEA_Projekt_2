//
// Created by Szef on 25.11.2023.
//

#ifndef PEA_PROJEKT2_TSPGRAPH_H
#define PEA_PROJEKT2_TSPGRAPH_H


#include <vector>


class TSPGraph {
private:
    int verticesNumber;
    int** adjacencyMatrix;                      //macierz sąsiedztwa - tablica dwuwymiarowa

//    std::vector<std::vector<int>> getNeighborhoodSolutions(std::vector<int> tour);
//    std::vector<int> swapPositions(std::vector<int> tour, int index1, int index2);
//    bool candidateInTabooList(std::vector<std::vector<int>>& tabooList, std::vector<int>& candidate);

public:
    explicit TSPGraph(int verticesNumber);
    TSPGraph();
    TSPGraph(int verticesNumber, int**& adjacencyMatrix);
    ~TSPGraph();
    int** getAdjMatrix();
    int getVerticesNumber();

    void loadMatrix(int verticesCount, int **&matrix);
    int addEdgeCost(int tail, int head, int cost);       //zwraca -1 jak operacja nie mozliwa - gdy tail = head

    std::vector<int> greedyTSP();                       //zwraca sciezke uzyskana za pomoca metody zachlannej

//    std::vector<int> tabuSearch(int iterations, int tabooSize, std::vector<int> initialSolution);

    int calculateTour(std::vector<int> tour);
};


#endif //PEA_PROJEKT2_TSPGRAPH_H
