#include <iostream>
#include <vector>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"
#include "algorithms/TabooSearch.h"
#include "tests/Test.h"

using namespace std;

void menu();
void menuChoseNeighborhood();
void testsDialog();
void test();

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
                "5. Zapis sciezki rozwiazania do pliku (txt).\n"
                "6. Obliczenie wartosci sciezki z pliku (txt).\n"
                "7. Testy.\n"
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

                    solution = ts->run(graph->getVerticesNumber() * 100, solution);
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
            case '6':
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
            case '7':
                testsDialog();
                break;
        }
    }while (choice != '0');

    delete graph;
    delete ts;
}

void menuChoseNeighborhood()
{
    cout << "Wybierz sasiedztwo:\n"
            "1. Swap (domyslny).\n"
            "2. Reverse.\n"
            "3. Insert.\n"
            "Wprowadz numer: ";
}

void testsDialog()
{
    cout << "Pliki: ftv55.xml, ftv170.xml, rbg380 musza znajdowac sie w tym samym folderze co plik wykonywany .exe\n"
            "Przewidywany czas testu: 6h\n"
            "Kontynuowac? 'T' - tak, 'N' - nie\n";
    char ans = 'N';
    cin >> ans;
    switch(ans)
    {
        default:
            cout << "Nie ma takiej opcji." << endl;
        case 'N':
            break;
        case 'T':
            test();
            break;
    }
}


void test()
{
    Test::generateFile_BestSolutionInTime_ftv55(10, 120);
    Test::generateFile_BestSolutionInTime_ftv170(10, 240);
    Test::generateFile_BestSolutionInTime_rbg358(10, 360);

//    Test::generateFile_BestSolutionInTime_ftv55v2(10, 120);
//    Test::generateFile_BestSolutionInTime_ftv170v2(10, 240);
//    Test::generateFile_BestSolutionInTime_rbg358v2(10, 360);
}