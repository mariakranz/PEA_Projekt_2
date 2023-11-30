//
// Created by Szef on 29.11.2023.
//

#include "TabooSearch.h"

TabooSearch::TabooSearch( TSPGraph *&graph1) {
    graph = graph1;
    chosenNeighborhoodType = swap;
    maxTime = 0;
}


TabooSearch::TabooSearch() {
    graph = nullptr;
    chosenNeighborhoodType = swap;
    maxTime = 0;
}



std::vector<int> TabooSearch::swapPositions(std::vector<int> tour, int index1, int index2) {
    if(index1 >= tour.size() || index2 >= tour.size()) return {};
    std::swap(tour[index1], tour[index2]);
    return tour;
}

std::vector<int> TabooSearch::reverseNumbers(std::vector<int> tour, int startingIndex, int endingIndex) {
    if(startingIndex >= tour.size() || endingIndex >= tour.size()) return {};
    if (startingIndex > endingIndex){
        int tmp = startingIndex;
        startingIndex = endingIndex;
        endingIndex = tmp;
    }

    while (startingIndex < endingIndex) {
        // Zamień elementy na końcach zakresu
        std::swap(tour[startingIndex], tour[endingIndex]);

        // Przesuń indeksy wewnątrz zakresu
        ++startingIndex;
        --endingIndex;
    }
    return tour;
}

std::vector<int> TabooSearch::insertBeforeNumber(std::vector<int> tour, int numberIndex, int targetIndex) {
    if(numberIndex >= tour.size() || targetIndex >= tour.size()) return {};

    int number = tour[numberIndex];
    tour.insert(tour.begin() + targetIndex, number);
    return tour;
}

std::vector<std::vector<int>> TabooSearch::getNeighborhoodSolutions(std::vector<int> tour) {
    std::vector<std::vector<int>> neighborhoodSolutions;

    switch (chosenNeighborhoodType) {
        case swap:
            for(int i = 0; i < tour.size(); i++) {
                for (int j = 0; j < tour.size(); j++) {
                    if (i == j) continue;
                    neighborhoodSolutions.push_back(swapPositions(tour, i, j));
                }
            }
            break;
        case reverse:
            for(int i = 0; i < tour.size()/2; i++) {
                for (int j = 0; j < tour.size(); j++) {
                    if (i == j) continue;
                    neighborhoodSolutions.push_back(reverseNumbers(tour, i, j));
                }
            }
            break;
        case insert:
            for(int i = 0; i < tour.size(); i++) {
                for (int j = 0; j < tour.size(); j++) {
                    if (i == j) continue;
                    neighborhoodSolutions.push_back(insertBeforeNumber(tour, i, j));;
                }
            }
            break;
    }
//    for(int i = 1; i < tour.size() - 1; i++){
//        for(int j = 1; j < tour.size() - 1; j++) {
//            if (i == j) continue;
//
//            switch (chosenNeighborhoodType) {
//                case swap:
//                    neighborhoodSolutions.push_back(swapPositions(tour, i, j));
//                    break;
//                case reverse:
//                    neighborhoodSolutions.push_back(reverseNumbers(tour, i, j));
//                    break;
//                case insert:
//                    neighborhoodSolutions.push_back(insertBeforeNumber(tour, i, j));
//                    break;
//            }
//            ;
//        }
//    }

    return neighborhoodSolutions;
}

bool TabooSearch::candidateInTabooList(std::vector<std::vector<int>> &tabooList, std::vector<int> &candidate) {
    for(std::vector<int> element: tabooList){
        if (std::equal(element.begin(), element.end(), candidate.begin(), candidate.end())) return true;
    }
    return false;
}

std::vector<int> TabooSearch::tabuSearch(int iterations, int tabooSize, const std::vector<int>& initialSolution) {
    std::vector<int> bestSolution = initialSolution;
    std::vector<int> bestCandidate = initialSolution;
    std::vector<std::vector<int>> tabooList;
    tabooList.push_back(initialSolution);

    //std::vector<std::vector<int>> tabu(graph->getVerticesNumber() - 1, std::vector<int>(graph->getVerticesNumber() - 1, 0));

    for(; iterations > 0; iterations--){
        std::vector<std::vector<int>> neighborhoodSolutions = getNeighborhoodSolutions(bestCandidate);
        bestCandidate = neighborhoodSolutions[0];
        unsigned long  long g = neighborhoodSolutions.size();   //niepotrzebne

        for(std::vector<int> candidate: neighborhoodSolutions){
            int candidateCost = graph->calculateTour(candidate);
            int bestCandidateTour = graph->calculateTour(bestCandidate);
            if((candidateCost < bestCandidateTour) && !candidateInTabooList(tabooList, candidate)){
                bestCandidate = candidate;
            }
        }

        if(graph->calculateTour(bestCandidate) < graph->calculateTour(bestSolution)){
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

std::vector<int> TabooSearch::tabuSearchV2(int iterations, const std::vector<int> &initialSolution) {
    int vertNum = graph->getVerticesNumber();
    std::vector<int> bestSolution = initialSolution;
    std::vector<int> bestCandidate = initialSolution;
    //std::vector<std::vector<int>> tabooMatrix(vertNum, std::vector<int>(vertNum, 0));    //tablica duwymiarowa N x N, wszedzie wartosc 0
    std::vector<int> tabooList(vertNum, 0);

    for(; iterations > 0; iterations--){

//        for (int i = 0; i < vertNum; i++){
//            for (int j = 0; j < vertNum ; j++){
//                if (tabooMatrix[i][j] > 0)
//                    tabooMatrix[i][j]--;
//            }
//        }
        for(int i = 0; i < vertNum; i++){
            if (tabooList[i] > 0){
                tabooList[i]--;
            }
        }


        std::vector<std::vector<int>> neighborhoodSolutions = getNeighborhoodSolutions(bestCandidate);
        bestCandidate = neighborhoodSolutions[0];

        for(std::vector<int> candidate: neighborhoodSolutions){
            int candidateCost = graph->calculateTour(candidate);
            int bestCandidateTour = graph->calculateTour(bestCandidate);
//            if((candidateCost < bestCandidateTour) && !candidateInTabooList(tabooList, candidate)){
//                bestCandidate = candidate;
//            }
        }

        if(graph->calculateTour(bestCandidate) < graph->calculateTour(bestSolution)){
            bestSolution = bestCandidate;
        }

//        tabooList.push_back(bestCandidate);
//        if(tabooList.size() > tabooSize){
//            tabooList.erase(tabooList.begin());
//        }
    }

    std::destroy(bestCandidate.begin(), bestCandidate.end());
    return bestSolution;
}

void TabooSearch::setNeighborhoodType(neighborhoodType newNeighborhoodType) {
    chosenNeighborhoodType = newNeighborhoodType;
}

void TabooSearch::setGraph(TSPGraph *&graph1) {
    graph = graph1;
}

void TabooSearch::setMaxTime(int time) {
    maxTime = time;
}


