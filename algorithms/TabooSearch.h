//
// Created by Szef on 29.11.2023.
//

#ifndef PEA_PROJEKT2_TABOOSEARCH_H
#define PEA_PROJEKT2_TABOOSEARCH_H


#include <vector>
#include "../graph/TSPGraph.h"

enum neighborhoodType{swap = 1, reverse = 2, insert = 3};

class TabooSearch {
private:
    TSPGraph* graph;
    neighborhoodType chosenNeighborhoodType;
    int stopTime;                                //[s]
    //int chosenNeighborhoodType;
    double bestSolutionFoundTime;


    //3 definicje sasiedztwa
    std::vector<int> swapPositions(std::vector<int> tour, int index1, int index2);
    std::vector<int> reverseNumbers(std::vector<int> tour, int startingIndex, int endingIndex);
    std::vector<int> insertBeforeNumber(std::vector<int> tour, int numberIndex, int targetIndex);

    std::vector<std::vector<int>> getNeighborhoodSolutions(std::vector<int> tour);
    bool candidateInTabooList(std::vector<std::vector<int>>& tabooList, std::vector<int>& candidate);

    std::vector<int> randomSolution(int verticesNumber);
    std::vector<int> shuffleHalf(std::vector<int> path);

public:
    explicit TabooSearch( TSPGraph *&graph1);
    TabooSearch();
    std::vector<int> tabuSearch(int iterations, int tabooSize, const std::vector<int>& initialSolution);
    std::vector<int> tabuSearchV2(int iterations, const std::vector<int>& initialSolution);
    std::vector<int> run(int tabooSize, const std::vector<int>& initialSolution);

    void setGraph(TSPGraph *&graph1);
    void setStopTime(int time);
    void setNeighborhoodType(neighborhoodType newNeighborhoodType);
    double getBestSolutionFoundTime();
    int getStopTime();
    std::string getNeighborhoodType();
};


#endif //PEA_PROJEKT2_TABOOSEARCH_H
