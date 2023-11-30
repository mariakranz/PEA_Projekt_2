//
// Created by Szef on 29.11.2023.
//

#ifndef PEA_PROJEKT2_TABOOSEARCH_H
#define PEA_PROJEKT2_TABOOSEARCH_H


#include <vector>
#include "../graph/TSPGraph.h"

class TabooSearch {
private:
    TSPGraph* graph;


    std::vector<int> swapPositions(std::vector<int> tour, int index1, int index2);
    std::vector<std::vector<int>> getNeighborhoodSolutions(std::vector<int> tour);
    bool candidateInTabooList(std::vector<std::vector<int>>& tabooList, std::vector<int>& candidate);

public:
    explicit TabooSearch( TSPGraph *&graph1);
    std::vector<int> tabuSearch(int iterations, int tabooSize, const std::vector<int>& initialSolution);
};


#endif //PEA_PROJEKT2_TABOOSEARCH_H
