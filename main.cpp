#include <iostream>
#include <vector>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    TSPGraph* graph = DataReader::createGraphFromTheData("ftv55.xml");                           //ftv55.atsp(1608), ftv170.atsp (2755) , rgb358.atsp (1163)
    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());

    std::vector<int> solution = graph->greedyTSP();

    // Wyświetlenie rozwiązania
    std::cout << "Trasa: ";
    for (int city : solution) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    std::cout << "Koszt: " << graph->calculateTour(solution) << std::endl;

    //solution = { 0, 2, 3, 5, 4, 1};
    //solution = { 0, 2, 1, 3, 4, 5};
    std::vector<int> solutionTSP = graph->tabuSearch(1000, 10, solution);
    std::cout << "Trasa: ";
    for (int city : solutionTSP) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    std::cout << "Koszt: " << graph->calculateTour(solutionTSP) << std::endl;
//    double *path = graph->tabuSearch();
//    cout << endl;
//    for(int i = 0; i < graph->getVerticesNumber(); i++){
//        cout << path[i] << " -> ";
//    }
//    cout << endl;

    delete graph;
    return 0;
}
