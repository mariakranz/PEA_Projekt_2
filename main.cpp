#include <iostream>
#include <vector>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"
#include "algorithms/TabooSearch.h"

using namespace std;

void menu();
void menuChoseNeighborhood();

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    menu();
    return 0;
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
                "1. Wczytanie danych z pliku (xml).\n"
                "2. Wprowadzenie kryterium stopu.\n"
                "3. Wybor sasiedztwa (taboo search).\n"
                "4. Uruchomienie algorytmu Taboo search.\n"
                "5. (nz)Ustawienie wspolczynnika zmiany temperatury dla SW.\n"
                "6. (nz)Uruchomienie algorytmu SW.\n"
                "7. Zapis sciezki rozwiazania do pliku (txt).\n"
                "8. Obliczenie wartosci sciezki z pliku (txt).\n"
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
                graph = DataReader::createGraphFromFile(filePath.c_str());
                if (graph != nullptr){
                    ts->setGraph(graph);
                    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());
                }else{
                    cerr << "Bledy przy odczytywaniu danych." << endl;
                }
                break;
            case '2':
                cout << "Podaj czas [s]: ";
                cin >> time;
                ts->setStopTime(time);
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
                    cout << "Koszt: " << graph->calculateTour(solution) << endl << endl;


                    cout << "Algorytm Tabu Search" << endl;
                    cout << "Warunek stopu: " << ts->getStopTime() << "s." << endl;
                    cout << "Sasiedztwo: " << ts->getNeighborhoodType() << endl;

                    solution = ts->run(500, solution);
                    cout << "Trasa: ";
                    for (int city : solution) {
                        cout << city << " ";
                    }
                    cout << endl;
                    cout << "Koszt: " << graph->calculateTour(solution) << endl;
                    cout << "Najlepsze rozwiazanie znalezione po " << ts->getBestSolutionFoundTime() << "s." << endl;
                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                if(!solution.empty()){
                    cout << "Podaj nazwe pliku: ";
                    cin >> filePath;
                    if(DataReader::savePathToFile(solution, filePath.c_str()) == -1){
                        cout << "Blad przy zapisie do pliku." << endl;
                    }else{
                        cout << "Zapisano w pliku " << filePath << "." << endl;
                    }
                }else{
                    cout << "Nie wygenerowano rozwiazania" << endl;
                }
                break;
            case '8':
                if(graph){
                    cout << "Podaj nazwe pliku: ";
                    cin >> filePath;
                    int result = -1;
                    result = DataReader::calculatePathFromFile(filePath.c_str(), graph);
                    if(result == - 1){
                        cout << "Blad przy odczytywaniu pliku." << endl;
                    }else{
                        cout << "Koszt: " << result << endl;
                    }
                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }
                break;
            case '9':
                break;
        }
    }while (choice != '0');

    delete graph;
    delete ts;
}

void menuChoseNeighborhood(){
    cout << "Wybierz sasiedztwo:\n"
            "1. Swap (domyslny).\n"
            "2. Reverse.\n"
            "3. Insert.\n"
            "Wprowadz numer: ";
}