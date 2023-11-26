//
// Created by Szef on 25.11.2023.
//

#ifndef PEA_PROJEKT2_DATAREADER_H
#define PEA_PROJEKT2_DATAREADER_H


#include <string>
#include "../graph/TSPGraph.h"

class DataReader {
private:
    static int extractNumber(const char* input);

public:
    static TSPGraph* createGraphFromTheData(const char* filePath);
    static TSPGraph* createRandomGraph(int verticesNumber);
};


#endif //PEA_PROJEKT2_DATAREADER_H
