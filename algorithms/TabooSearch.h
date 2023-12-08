//
// Created by Szef on 29.11.2023.
//

#ifndef PEA_PROJEKT2_TABOOSEARCH_H
#define PEA_PROJEKT2_TABOOSEARCH_H


#include <vector>
#include <list>
#include "../graph/TSPGraph.h"

enum neighborhoodType{swap = 1, reverse = 2, insert = 3};

class TabooSearch {
private:
    TSPGraph* graph;
    neighborhoodType chosenNeighborhoodType;
    int stopTime;                                //[s]
    double bestSolutionFoundTime;


    //3 definicje sasiedztwa
    std::vector<int> swapPositions(std::vector<int> tour, int index1, int index2);
    std::vector<int> reverseNumbers(std::vector<int> tour, int startingIndex, int endingIndex);
    std::vector<int> insertBeforeNumber(std::vector<int> tour, int numberIndex, int targetIndex);           //fixme - zle dziala

    std::list<std::vector<int>> getNeighborhoodSolutions(std::vector<int> tour);                    //zwraca liste sasiadow
    bool candidateInTabooList(std::list<std::vector<int>>& tabooList, std::vector<int>& candidate); //zwraca czy kandydat znajduje sie w liscie tabu

    std::vector<int> randomSolution(int verticesNumber);                                            //generuje zupelnie randomowa sciezke
    std::vector<int> shuffleHalf(std::vector<int> path);                                            //generuje randomowa polowe

public:
    TabooSearch();
    std::vector<int> run(int tabooSize, const std::vector<int>& initialSolution);                   //rozpoczyna algorytm Tabu Search



    void setGraph(TSPGraph *&graph1);
    void setStopTime(int time);
    void setNeighborhoodType(neighborhoodType newNeighborhoodType);
    double getBestSolutionFoundTime();
    int getStopTime();
    std::string getNeighborhoodType();


    std::vector<int> runTests(int tabooSize, const std::vector<int>& initialSolution, const char* filePath);        //rozpoczyna algorytm Tabu Search i zapisuje wyniki do pliku
};


#endif //PEA_PROJEKT2_TABOOSEARCH_H
