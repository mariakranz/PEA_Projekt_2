//
// Created by Szef on 25.11.2023.
//

#include <iostream>
#include "DataReader.h"
#include "../xmlParser/tinyxml2.h"
#include "../graph/TSPGraph.h"
#include "../structures/ListImpl.h"


TSPGraph *DataReader::createGraphFromTheData(const char* filePath) {
    tinyxml2::XMLDocument xmlDoc;

    // Ładowanie pliku XML
    if (xmlDoc.LoadFile(filePath) == tinyxml2::XML_SUCCESS) {
        // Pobieranie korzenia dokumentu
        tinyxml2::XMLElement* root = xmlDoc.RootElement();

        // Sprawdzanie, czy korzeń jest poprawny
        if (root && strcmp(root->Name(), "travellingSalesmanProblemInstance") == 0) {

            int verticesNumber = extractNumber(filePath);
            if (verticesNumber == -1) return nullptr;

//            verticesNumber ++;
            // Pobieranie danych z elementów
//            int verticesNumber = 0;
            TSPGraph* newGraph = new TSPGraph(verticesNumber);

            const char* name = root->FirstChildElement("name")->GetText();
            const char* source = root->FirstChildElement("source")->GetText();
            const char* description = root->FirstChildElement("description")->GetText();
            int doublePrecision = 0;
            root->FirstChildElement("doublePrecision")->QueryIntText(&doublePrecision);
            int ignoredDigits = 0;
            root->FirstChildElement("ignoredDigits")->QueryIntText(&ignoredDigits);

            std::cout << "Name: " << name << std::endl;
            std::cout << "Source: " << source << std::endl;
            std::cout << "Description: " << description << std::endl;
            std::cout << "Double Precision: " << doublePrecision << std::endl;
            std::cout << "Ignored Digits: " << ignoredDigits << std::endl;

            // Przechodzenie przez elementy "vertex"
            tinyxml2::XMLElement* vertexElement = root->FirstChildElement("graph")->FirstChildElement("vertex");
            int row = 0;
            int vertCount = 0;
            ListImpl* firstRowList = new ListImpl();
            while (vertexElement) {
                std::cout << "Vertex:" << std::endl;

                // Przechodzenie przez elementy "edge"
                tinyxml2::XMLElement* edgeElement = vertexElement->FirstChildElement("edge");
                while (edgeElement) {
                    const char* costAttribute = edgeElement->Attribute("cost");
                    double cost = std::stod(costAttribute);
                    const char* edgeValue = edgeElement->GetText();
                    int column = std::stoi(edgeValue);

                    if (costAttribute && edgeValue) {
                        std::cout << "  Edge Value: " << edgeValue << ", Cost: " << cost << std::endl;
                    }

//                    if (row == 0){
//                        firstRowList->listInsertTail(cost);
//                    }else{
//                        newGraph->addEdgeCost(row, column, cost);
//                    }

                    newGraph->addEdgeCost(row, column, cost);

                    // Przechodzenie do następnego elementu "edge"
                    edgeElement = edgeElement->NextSiblingElement("edge");
                }
                if(row == 0){

                }

                // Przechodzenie do następnego elementu "vertex"
                vertexElement = vertexElement->NextSiblingElement("vertex");

                row++;
            }
            return newGraph;
        } else {
            std::cerr << "Błąd: Nieprawidłowy format pliku XML." << std::endl;
        }
    } else {
        std::cerr << "Błąd: Nie można załadować pliku XML." << std::endl;
    }

    return nullptr;
}

int DataReader::extractNumber(const char* input) {
    std::string numberStr;

    // Przechodzenie przez każdy znak w ciągu znaków
    while (*input) {
        // Jeśli znak jest cyfrą lub jest pierwszym znakiem po "u" (jeśli "u" jest prefiksem),
        // to dodajemy go do ciągu cyfr
        if (std::isdigit(*input) || (*input == 'u' && numberStr.empty())) {
            numberStr += *input;
        } else if (!numberStr.empty()) {
            // Jeśli napotkamy coś innego niż cyfra i mamy już cyfry w numberStr, to przerywamy pętlę
            break;
        }

        // Przesunięcie do następnego znaku
        ++input;
    }

    // Konwersja ciągu cyfr na liczbę
    try {
        return std::stoi(numberStr);
    } catch (const std::invalid_argument& e) {
        // Błąd konwersji
        std::cerr << "Błąd konwersji: " << e.what() << std::endl;
        return -1; // Wartość domyślna w przypadku błędu
    }
}