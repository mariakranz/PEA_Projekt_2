#include <iostream>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    TSPGraph* graph = DataReader::createGraphFromTheData("a10.xml");                           //ftv55.atsp(1608), ftv170.atsp (2755) , rgb358.atsp (1163)
    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());


    delete graph;
    return 0;
}
