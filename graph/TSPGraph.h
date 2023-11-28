//
// Created by Szef on 25.11.2023.
//

#ifndef PEA_PROJEKT2_TSPGRAPH_H
#define PEA_PROJEKT2_TSPGRAPH_H


class TSPGraph {
private:
    int verticesNumber;
    double** adjacencyMatrix;                      //macierz sąsiedztwa - tablica dwuwymiarowa
    //int loadDataFromFile(const char* filePath);



public:
    explicit TSPGraph(int verticesNumber);
    TSPGraph();
    TSPGraph(int verticesNumber, double**& adjacencyMatrix);
    ~TSPGraph();
    double** getAdjMatrix();
    int getVerticesNumber();

    void loadMatrix(int verticesCount, double **&matrix);
    int addEdgeCost(int tail, int head, double cost);       //zwraca -1 jak operacja nie mozliwa - gdy tail = head

    double* tabuSearch();

};


#endif //PEA_PROJEKT2_TSPGRAPH_H
