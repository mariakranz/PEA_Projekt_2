//
// Created by Szef on 25.11.2023.
//

#include <climits>
#include <iostream>
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

std::vector<int> TSPGraph::greedyTSP() {
    std::vector<bool> visited(verticesNumber, false);
    std::vector<int> path;
    path.reserve(verticesNumber);

    // Wybieramy pierwsze miasto jako startowe
    int currentVertex = 0;
    path.push_back(currentVertex);
    visited[currentVertex] = true;

    for (int i = 1; i < verticesNumber; ++i) {
        int minDistance = INT_MAX;
        int nextVertex = -1;

        // Szukamy najbliższego nieodwiedzonego miasta
        for (int j = 0; j < verticesNumber; ++j) {
            if (!visited[j]) {
                int distance = adjacencyMatrix[currentVertex][j];
                if (distance < minDistance) {
                    minDistance = distance;
                    nextVertex = j;
                }
            }
        }

        // Dodajemy najbliższe miasto do ścieżki
        path.push_back(nextVertex);
        visited[nextVertex] = true;
        currentVertex = nextVertex;
    }

    std::destroy(visited.begin(), visited.end());
    return path;
}

int TSPGraph::calculateTour(std::vector<int> tour) {
    int res = 0;
    for(int i = 0; i < verticesNumber - 1; i++){
        res+= adjacencyMatrix[tour[i]][tour[i+1]];
    }
    res+= adjacencyMatrix[tour.back()][tour.front()];
    return res;
}

std::vector<int> TSPGraph::tabuSearch(int iterations, int tabooSize, std::vector<int> initialSolution) {
    std::vector<int> bestSolution = initialSolution;
    std::vector<int> bestCandidate = initialSolution;
    std::vector<std::vector<int>> tabooList;
    tabooList.push_back(initialSolution);

    for(; iterations > 0; iterations--){
        std::vector<std::vector<int>> neighborhoodSolutions = getNeighborhoodSolutions(bestCandidate);
        bestCandidate = neighborhoodSolutions[0];

        for(std::vector<int> candidate: neighborhoodSolutions){
            int candidateCost = calculateTour(candidate);
            int bestCandidateTour = calculateTour(bestCandidate);
            if((candidateCost < bestCandidateTour) && !candidateInTabooList(tabooList, candidate)){
                bestCandidate = candidate;
            }
        }

        if(calculateTour(bestCandidate) < calculateTour(bestSolution)){
            bestSolution = bestCandidate;
        }

        tabooList.push_back(bestCandidate);
        if(tabooList.size() > tabooSize){
            tabooList.erase(tabooList.begin());
        }
    }

    std::destroy(bestCandidate.begin(), bestCandidate.end());
    return bestSolution;
}

std::vector<std::vector<int>> TSPGraph::getNeighborhoodSolutions(std::vector<int> tour) {
    std::vector<std::vector<int>> neighborhoodSolutions;

    for(int i = 1; i < tour.size() - 1; i++){
        for(int j = 1; j < tour.size() - 1; j++) {
            if (i == j) continue;
            neighborhoodSolutions.push_back(swapPositions(tour, i, j));
        }
    }

    return neighborhoodSolutions;
}

std::vector<int> TSPGraph::swapPositions(std::vector<int> tour, int index1, int index2) {
    if (index1 < tour.size() && index2 < tour.size()) {
        std::swap(tour[index1], tour[index2]);
        return tour;
    }
    return {};
}

bool TSPGraph::candidateInTabooList(std::vector<std::vector<int>> &tabooList, std::vector<int> &candidate) {
    for(std::vector<int> element: tabooList){
        if (std::equal(element.begin(), element.end(), candidate.begin(), candidate.end())) return true;
    }
    return false;
}




