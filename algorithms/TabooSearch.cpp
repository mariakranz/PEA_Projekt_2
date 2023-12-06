//
// Created by Szef on 29.11.2023.
//

#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include "TabooSearch.h"

TabooSearch::TabooSearch( TSPGraph *&graph1) {
    graph = graph1;
    chosenNeighborhoodType = swap;
    stopTime = 30;   //[s]
    bestSolutionFoundTime = 0;
}


TabooSearch::TabooSearch() {
    graph = nullptr;
    chosenNeighborhoodType = swap;
    stopTime = 30;
    bestSolutionFoundTime = 0;
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
//    int rand = std::rand() % 2;
//    std::uniform_int_distribution<int> distribution(0, 1);

    switch (chosenNeighborhoodType) {
        case swap:
            for(int i = 0; i < tour.size() - 1; i++) {
                for (int j = i + 1; j < tour.size(); j++) {
                    neighborhoodSolutions.push_back(swapPositions(tour, i, j));
                }
            }

            break;
        case reverse:
            for(int i = 0; i < tour.size() - 1; i++) {
                for (int j = i + 1; j < tour.size(); j++) {
                    if (i == j) continue;
                    neighborhoodSolutions.push_back(reverseNumbers(tour, i, j));
                }
            }
            break;
        case insert:
            for(int i = 0; i < tour.size() - 1; i++) {
                for (int j = i + 1; j < tour.size(); j++) {
                    neighborhoodSolutions.push_back(insertBeforeNumber(tour, j, i));;
                }
            }
            break;
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

void TabooSearch::setStopTime(int time) {
    stopTime = time;
}

std::vector<int> TabooSearch::run(int tabooSize, const std::vector<int> &initialSolution) {
    std::vector<int> bestSolution = initialSolution;
    std::vector<int> bestCandidate = initialSolution;

    std::vector<std::vector<int>> tabooList(tabooSize);     // fixme: zmienic na list
    tabooList.push_back(initialSolution);
    //int maxNoImprovement = graph->getVerticesNumber() / 10;
    int maxNoImprovement = 7 * graph->getVerticesNumber();
    int noImprovementCount = 0;

    //std::vector<std::vector<int>> tabu(graph->getVerticesNumber() - 1, std::vector<int>(graph->getVerticesNumber() - 1, 0));
    const std::clock_t start_time = std::clock();

    while ((std::clock() - start_time) / CLOCKS_PER_SEC < stopTime) {
        std::vector<std::vector<int>> neighborhoodSolutions = getNeighborhoodSolutions(bestCandidate);
        bestCandidate = neighborhoodSolutions[0];
        int bestCandidateCost = graph->calculateTour(bestCandidate);
        //unsigned long  long g = neighborhoodSolutions.size();   //niepotrzebne


        for(std::vector<int> candidate: neighborhoodSolutions){     //znajdz najlepszego sasiada
            if((std::clock() - start_time) / CLOCKS_PER_SEC >= stopTime) break;

            int candidateCost = graph->calculateTour(candidate);

            if((candidateCost < bestCandidateCost) && !candidateInTabooList(tabooList, candidate) && candidateCost >= 0){
                //std::cout << bestCandidateCost << ": " << candidateCost << std::endl;
                bestCandidate = candidate;
                bestCandidateCost = candidateCost;

            }
        }

        if(bestCandidateCost < graph->calculateTour(bestSolution)){
            bestSolution = bestCandidate;
            bestSolutionFoundTime = (std::clock() - (double)start_time) / CLOCKS_PER_SEC;
            std::cout << "Rozw: " << bestCandidateCost << " Czas:" << bestSolutionFoundTime << std::endl;
        }else{
            noImprovementCount++;
        }

        tabooList.push_back(bestCandidate);         //update taboo
        if(tabooList.size() > tabooSize){
            tabooList.erase(tabooList.begin());
        }

        if (noImprovementCount >= maxNoImprovement) {           //jesli od dawna nie bylo zmiany (minimum lokalne) - wylosuj sciezke
            //bestCandidate = randomSolution(graph->getVerticesNumber());
            bestCandidate = shuffleHalf(bestSolution);
            //std::cout << "Losowanie" << std::endl;
            noImprovementCount = 0;
        }
    }
    std::cout << "All time:" << (std::clock() - start_time) / CLOCKS_PER_SEC << std::endl;

    //std::destroy(bestCandidate.begin(), bestCandidate.end());
    return bestSolution;
}

std::vector<int> TabooSearch::randomSolution(int verticesNumber) {
    std::vector<int> randomPath(verticesNumber);
    for (int i = 0; i < verticesNumber; ++i) {
        randomPath[i] = i;
    }
    //std::random_shuffle(randomPath.begin(), randomPath.end());
    std::shuffle(randomPath.begin(), randomPath.end(), std::mt19937(std::random_device()()));
    return randomPath;
}

double TabooSearch::getBestSolutionFoundTime() {
    return bestSolutionFoundTime;
}

int TabooSearch::getStopTime() {
    return stopTime;
}

std::string TabooSearch::getNeighborhoodType() {
    switch(chosenNeighborhoodType){
        case swap: return "swap";
        case reverse: return "reverse";
        case insert: return "insert";
    }
    return "";
}

std::vector<int> TabooSearch::shuffleHalf(std::vector<int> path) {
    int sizeOfShuffle = (int)path.size() / 5;

    int rand = std::rand() % 2;
    std::uniform_int_distribution<int> distribution(0, 1);
    if(rand == 0){      //wymieszaj od polowy sciezki
        std::shuffle(path.begin() + (int)(path.size() / 2), path.end(), std::mt19937(std::random_device()()));
        //std::shuffle(path.begin() + 4 * sizeOfShuffle, path.end(), std::mt19937(std::random_device()()));

    }else{              //wymieszaj do polowy sciezki
        std::shuffle(path.begin() , path.end() - (int)(path.size() / 2), std::mt19937(std::random_device()()));
        //std::shuffle(path.begin() , path.end() - 4 * sizeOfShuffle, std::mt19937(std::random_device()()));
    }

    return path;
}


