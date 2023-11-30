#include <iostream>
#include <vector>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"
#include "algorithms/TabooSearch.h"

using namespace std;

void menu();
void menuChoseNeighborhood();
void temp();

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    menu();
    //temp();

    return 0;

}

void temp(){

    TSPGraph* graph = DataReader::createGraphFromTheData("ftv6_1.xml");                           //ftv55.atsp(1608), ftv170.atsp (2755) , rgb358.atsp (1163)
    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());

    std::vector<int> solution = graph->greedyTSP();

    // Wyświetlenie rozwiązania
    std::cout << "Trasa greedy: ";
    for (int city : solution) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    std::cout << "Koszt greedy: " << graph->calculateTour(solution) << std::endl;

    //solution = { 0, 2, 3, 5, 4, 1};
    //solution = { 0, 2, 1, 3, 4, 5};
//    std::vector<int> solutionTSP = graph->tabuSearch(1000, 10, solution);
//    std::cout << "Trasa: ";
//    for (int city : solutionTSP) {
//        std::cout << city << " ";
//    }
//    std::cout << std::endl;
//
//    std::cout << "Koszt: " << graph->calculateTour(solutionTSP) << std::endl;

    TabooSearch* ts = new TabooSearch(graph);
    solution = ts->tabuSearch(1000, 10, solution);
    std::cout << "Trasa: ";
    for (int city : solution) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    std::cout << "Koszt: " << graph->calculateTour(solution) << std::endl;

    delete graph;
}

void menu(){
    string filePath;
    TSPGraph *graph = nullptr;
    TabooSearch *ts = new TabooSearch();
    int time;
    int neighborhood;
    char choice;
    std::vector<int> solution;

    do{
        cout << "\n----MENU----\n"
                "1. Wczytanie danych z pliku.\n"
                "2. Wprowadzenie kryterium stopu.\n"
                "3. Wybor sasiedztwa (taboo search).\n"
                "4. Uruchomienie algorytmu Taboo search.\n"
                "5. (nz)Ustawienie wspolczynnika zmiany temperatury dla SW.\n"
                "6. (nz)Uruchomienie algorytmu SW.\n"
                "7. Zapis sciezki rozwiazania do pliku txt.\n"
                "8. Obliczenie wartosci sciezki z pliku txt.\n"
                "9. Testy.\n"
                "0. Wyjdz z programu.\n"
                "Wprowadz numer: ";
        cin >> choice;
        switch (choice) {
            default:
                cout << "Nie ma takiej opcji!\n";
                break;
            case '0': break;
            case '1':
                cout << "Podaj nazwe pliku: ";
                cin >> filePath;
                delete graph;                       //usun stary graf (jesli byl)
                graph = DataReader::createGraphFromTheData(filePath.c_str());
                if (graph != nullptr){
                    ts->setGraph(graph);
                    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());
                }else{
                    cerr << "Bledy przy odczytywaniu danych." << endl;
                }
                break;
            case '2':
                cout << "Podaj czas [ms]: ";
                cin >> time;
                ts->setMaxTime(time);
                break;
            case '3':
                menuChoseNeighborhood();
                cin >> neighborhood;
                ts->setNeighborhoodType(static_cast<neighborhoodType>(neighborhood));
                break;
            case '4':
                if(graph){
                    solution = graph->greedyTSP();

                    // Wyświetlenie rozwiązania
                    cout << "Algorytm zachlanny\n"
                            "Trasa: ";
                    for (int city : solution) {
                        cout << city << " ";
                    }
                    cout << endl;

                    cout << "Koszt: " << graph->calculateTour(solution) << endl;

//                    solution = graph->tabuSearch(1000, 10, solution);
//                    TabooSearch* ts = new TabooSearch(graph);

                    solution = ts->tabuSearch(1000, 10, solution);
                    cout << "Algorytm Tabu Search\n"
                            "Trasa: ";
                    for (int city : solution) {
                        cout << city << " ";
                    }
                    cout << endl;

                    cout << "Koszt: " << graph->calculateTour(solution) << endl;
                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }


                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
        }
    }while (choice != '0');
    delete graph;
}

void menuChoseNeighborhood(){
    cout << "Wybierz sasiedztwo:\n"
            "1. Swap.\n"
            "2. Reverse.\n"
            "3. Insert.\n";
}