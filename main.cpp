#include <iostream>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    TSPGraph* graph = DataReader::createGraphFromTheData("ft70.xml");                           //ftv55.atsp(1608), ftv170.atsp (2755) , rgb358.atsp (1163)
    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());
//    double *path = graph->tabuSearch();
//    cout << endl;
//    for(int i = 0; i < graph->getVerticesNumber(); i++){
//        cout << path[i] << " -> ";
//    }
//    cout << endl;

    delete graph;
    return 0;
}
