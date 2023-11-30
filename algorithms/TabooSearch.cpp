//
// Created by Szef on 29.11.2023.
//

#include "TabooSearch.h"

TabooSearch::TabooSearch( TSPGraph *&graph1) {
    graph = graph1;
}

std::vector<int> TabooSearch::swapPositions(std::vector<int> tour, int index1, int index2) {
    if (index1 < tour.size() && index2 < tour.size()) {
        std::swap(tour[index1], tour[index2]);
        return tour;
    }
    return {};
}

std::vector<std::vector<int>> TabooSearch::getNeighborhoodSolutions(std::vector<int> tour) {
    std::vector<std::vector<int>> neighborhoodSolutions;

    for(int i = 1; i < tour.size() - 1; i++){
        for(int j = 1; j < tour.size() - 1; j++) {
            if (i == j) continue;
            neighborhoodSolutions.push_back(swapPositions(tour, i, j));
        }
    }

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

    for(; iterations > 0; iterations--){
        std::vector<std::vector<int>> neighborhoodSolutions = getNeighborhoodSolutions(bestCandidate);
        bestCandidate = neighborhoodSolutions[0];

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


