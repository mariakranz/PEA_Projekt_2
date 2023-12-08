//
// Created by Szef on 29.11.2023.
//

#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include <list>
#include <fstream>
#include "TabooSearch.h"

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
        std::swap(tour[startingIndex], tour[endingIndex]);
        ++startingIndex;
        --endingIndex;
    }
    return tour;
}

std::vector<int> TabooSearch::insertBeforeNumber(std::vector<int> tour, int numberIndex, int targetIndex) {
    if(numberIndex >= tour.size() || targetIndex >= tour.size()) return {};

    int number = tour[numberIndex];
    tour.insert(tour.begin() + targetIndex, number);
    tour.erase(tour.begin() + numberIndex + 1);
    return tour;
}

std::list<std::vector<int>> TabooSearch::getNeighborhoodSolutions(std::vector<int> tour) {
    std::list<std::vector<int>> neighborhoodSolutions;

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
                    neighborhoodSolutions.push_back(insertBeforeNumber(tour, j, i));
                }
            }
            break;
    }

    return neighborhoodSolutions;
}

bool TabooSearch::candidateInTabooList(std::list<std::vector<int>> &tabooList, std::vector<int> &candidate) {
    for(const auto& element : tabooList) {
        if (candidate == element) {
            return true;
        }
    }
    return false;
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
    std::list<std::vector<int>> tabooList;
    tabooList.push_back(initialSolution);

    int maxNoImprovement = 7 * graph->getVerticesNumber();                                                       //maksymalna liczba iteracji bez poprawy wyniku
    int noImprovementCount = 0;

    const std::clock_t start_time = std::clock();                                                                //rozpocznij odliczanie zegara

    while ((std::clock() - start_time) / CLOCKS_PER_SEC < stopTime) {
        std::list<std::vector<int>> neighborhoodSolutions = getNeighborhoodSolutions(bestCandidate);        //pobierz liczbe sasiadow
        bestCandidate = neighborhoodSolutions.front();
        int bestCandidateCost = graph->calculateTour(bestCandidate);

        for(std::vector<int> candidate: neighborhoodSolutions){                                                  //znajdz najlepszego sasiada
            if((std::clock() - start_time) / CLOCKS_PER_SEC >= stopTime) break;                                  //sprawdzenie czy algorytm nie powinien zostac zakonczony
            int candidateCost = graph->calculateTour(candidate);

            if((candidateCost < bestCandidateCost) && !candidateInTabooList(tabooList, candidate)){           //jesli kandydat ma mnijeszy koszt i nie znajduje sie w liscie tabu, to przyjmij go jako najlepszego kandydata
                bestCandidate = candidate;                                                                          //fixme po naprawieniu insert usunac ostatni warunek
                bestCandidateCost = candidateCost;
            }
        }

        if(bestCandidateCost < graph->calculateTour(bestSolution)){                                     //jesli najlepszy kandydat jest lepszy niz najlepsze rozwiazanie, to przyjmij go jako najlepsze rozwiazanie
            bestSolution = bestCandidate;
            bestSolutionFoundTime = (std::clock() - (double)start_time) / CLOCKS_PER_SEC;
            std::cout << "Rozw: " << bestCandidateCost << " Czas:" << bestSolutionFoundTime << std::endl;
        }else{                                                                                                //w przeciwnym wypadku zinkrementuj licznik iteracji bez poprawy
            noImprovementCount++;
        }

        tabooList.push_back(bestCandidate);                                                                 //zaktualizuj liste tabu
        if(tabooList.size() > tabooSize){                                                                      //jesli lista przekroczyla swoj maks, usun najstarszy element (FIFO)
            tabooList.erase(tabooList.begin());
        }

        if (noImprovementCount >= maxNoImprovement) {                                                           //jesli od dawna nie bylo zmiany (minimum lokalne) - wylosuj sciezke
            bestCandidate = shuffleHalf(bestSolution);
            noImprovementCount = 0;
        }
    }

    return bestSolution;
}

std::vector<int> TabooSearch::randomSolution(int verticesNumber) {
    std::vector<int> randomPath(verticesNumber);
    for (int i = 0; i < verticesNumber; ++i) {
        randomPath[i] = i;
    }
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

std::vector<int> TabooSearch::runTests(int tabooSize, const std::vector<int> &initialSolution, const char* filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) return {};
    file << "time[s];value" << std::endl;

    std::vector<int> bestSolution = initialSolution;
    std::vector<int> bestCandidate = initialSolution;
    std::list<std::vector<int>> tabooList;
    tabooList.push_back(initialSolution);

    int maxNoImprovement = 7 * graph->getVerticesNumber();                                                       //maksymalna liczba iteracji bez poprawy wyniku
    int noImprovementCount = 0;

    const std::clock_t start_time = std::clock();                                                                //rozpocznij odliczanie zegara

    while ((std::clock() - start_time) / CLOCKS_PER_SEC < stopTime) {
        std::list<std::vector<int>> neighborhoodSolutions = getNeighborhoodSolutions(bestCandidate);        //pobierz liczbe sasiadow
        bestCandidate = neighborhoodSolutions.front();
        int bestCandidateCost = graph->calculateTour(bestCandidate);

        for(std::vector<int> candidate: neighborhoodSolutions){                                                  //znajdz najlepszego sasiada
            if((std::clock() - start_time) / CLOCKS_PER_SEC >= stopTime) break;                                  //sprawdzenie czy algorytm nie powinien zostac zakonczony
            int candidateCost = graph->calculateTour(candidate);

            if((candidateCost < bestCandidateCost) && !candidateInTabooList(tabooList, candidate)){           //jesli kandydat ma mnijeszy koszt i nie znajduje sie w liscie tabu, to przyjmij go jako najlepszego kandydata
                bestCandidate = candidate;
                bestCandidateCost = candidateCost;
            }
        }

        if(bestCandidateCost < graph->calculateTour(bestSolution)){                                     //jesli najlepszy kandydat jest lepszy niz najlepsze rozwiazanie, to przyjmij go jako najlepsze rozwiazanie
            bestSolution = bestCandidate;
            bestSolutionFoundTime = (std::clock() - (double)start_time) / CLOCKS_PER_SEC;
            file << bestSolutionFoundTime << ";" << bestCandidateCost << std::endl;
            std::cout << "Rozw: " << bestCandidateCost << " Czas:" << bestSolutionFoundTime << std::endl;
        }else{                                                                                                //w przeciwnym wypadku zinkrementuj licznik iteracji bez poprawy
            noImprovementCount++;
        }

        tabooList.push_back(bestCandidate);                                                                 //zaktualizuj liste tabu
        if(tabooList.size() > tabooSize){                                                                      //jesli lista przekroczyla swoj maks, usun najstarszy element (FIFO)
            tabooList.erase(tabooList.begin());
        }

        if (noImprovementCount >= maxNoImprovement) {                                                           //jesli od dawna nie bylo zmiany (minimum lokalne) - wylosuj sciezke
            bestCandidate = shuffleHalf(bestSolution);
            noImprovementCount = 0;
        }
    }

    file.close();
    return bestSolution;

}


