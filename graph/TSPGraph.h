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
//    TSPGraph();
    ~TSPGraph();
    double** getAdjMatrix();
    int getVerticesNumber() const;

    int addVerticle(int verticle);                          //dodaje rzad do macierzy sasiedztwa i powieksza liczbe wierzcholkow
    int addEdgeCost(int tail, int head, double cost);       //zwraca -1 jak operacja nie mozliwa - gdy tail = head

    void tabuSearch();
};


#endif //PEA_PROJEKT2_TSPGRAPH_H
