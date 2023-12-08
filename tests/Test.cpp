//
// Created by Szef on 07.12.2023.
//

#include <iostream>
#include "Test.h"
#include "../data/DataReader.h"
#include "../algorithms/TabooSearch.h"

void Test::generateFile_BestSolutionInTime_ftv55(int numberOfInstances, int time) {
    std::cout << "------Test ftv55.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;


    TSPGraph *graph;

    TabooSearch* ts = new TabooSearch();

    //ftv55.xml
    graph = DataReader::createGraphFromFile("ftv55.xml");
    if(graph)
    {
        std::vector<int> initSolution = graph->greedyTSP();
        ts->setGraph(graph);
        ts->setStopTime(time);
        //swap
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Swap Pilk " << i << std::endl;

            ts->setNeighborhoodType(swap);
            std::string filename = "ftv55_swap_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "ftv55_path_swap_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //reverse
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Reverse Pilk " << i << std::endl;

            ts->setNeighborhoodType(reverse);
            std::string filename = "ftv55_reverse_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "ftv55_path_reverse_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //insert
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Insert Pilk " << i << std::endl;

            ts->setNeighborhoodType(insert);
            std::string filename = "ftv55_insert_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "ftv55_path_insert_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }
    }
    delete ts;
    delete graph;

}

void Test::generateFile_BestSolutionInTime_ftv170(int numberOfInstances, int time) {
    std::cout << "------Test ftv170.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;

    TSPGraph *graph;

    TabooSearch* ts = new TabooSearch();

    //ftv170.xml
    graph = DataReader::createGraphFromFile("ftv170.xml");
    if(graph)
    {

        std::vector<int> initSolution = graph->greedyTSP();
        ts->setGraph(graph);
        ts->setStopTime(time);
        //swap
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Swap Pilk " << i << std::endl;

            ts->setNeighborhoodType(swap);

            std::string filename = "ftv170_swap_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "ftv170_path_swap_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //reverse
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Reverse Pilk " << i << std::endl;

            ts->setNeighborhoodType(reverse);
            std::string filename = "ftv170_reverse_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "ftv170_path_reverse_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //insert
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Insert Pilk " << i << std::endl;

            ts->setNeighborhoodType(insert);
            std::string filename = "ftv170_insert_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "ftv170_path_insert_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }
    }
    delete ts;
    delete graph;
}

void Test::generateFile_BestSolutionInTime_rbg358(int numberOfInstances, int time) {
    std::cout << "------Test rbg358.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;

    TSPGraph *graph;

    TabooSearch* ts = new TabooSearch();

    //rbg358.xml
    graph = DataReader::createGraphFromFile("rbg358.xml");
    if(graph)
    {
        std::vector<int> initSolution = graph->greedyTSP();
        ts->setGraph(graph);
        ts->setStopTime(time);

        //swap
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Swap Pilk " << i << std::endl;

            ts->setNeighborhoodType(swap);
            std::string filename = "rbg358_swap_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "rbg358_path_swap_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //reverse
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Reverse Pilk " << i << std::endl;

            ts->setNeighborhoodType(reverse);
            std::string filename = "rbg358_reverse_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "rbg358_path_reverse_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //insert
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Insert Pilk " << i << std::endl;

            ts->setNeighborhoodType(insert);
            std::string filename = "rbg358_insert_" + std::to_string(i) + ".txt";
            std::vector<int> res = ts->runTests(graph->getVerticesNumber()*100, initSolution, filename.c_str());

            std::string pathFilename = "rbg358_path_insert_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }
    }
    delete ts;
    delete graph;
}

void Test::generateFile_BestSolutionInTime_ftv55v2(int numberOfInstances, int time) {
    std::cout << "------Test ftv55.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;


    TSPGraph *graph;

    TabooSearch* ts = new TabooSearch();

    //ftv55.xml
    graph = DataReader::createGraphFromFile("ftv55.xml");
    if(graph)
    {
        std::vector<int> initSolution = graph->greedyTSP();
        ts->setGraph(graph);
        ts->setStopTime(time);
        //swap
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Swap Pilk " << i << std::endl;

            ts->setNeighborhoodType(swap);
            std::string filename = "ftv55_swap_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "ftv55_path_swap_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //reverse
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Reverse Pilk " << i << std::endl;

            ts->setNeighborhoodType(reverse);
            std::string filename = "ftv55_reverse_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "ftv55_path_reverse_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //insert
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Insert Pilk " << i << std::endl;

            ts->setNeighborhoodType(insert);
            std::string filename = "ftv55_insert_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "ftv55_path_insert_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }
    }
    delete ts;
    delete graph;

}

void Test::generateFile_BestSolutionInTime_ftv170v2(int numberOfInstances, int time) {
    std::cout << "------Test ftv170.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;

    TSPGraph *graph;

    TabooSearch* ts = new TabooSearch();

    //ftv170.xml
    graph = DataReader::createGraphFromFile("ftv170.xml");
    if(graph)
    {

        std::vector<int> initSolution = graph->greedyTSP();
        ts->setGraph(graph);
        ts->setStopTime(time);
        //swap
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Swap Pilk " << i << std::endl;

            ts->setNeighborhoodType(swap);

            std::string filename = "ftv170_swap_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "ftv170_path_swap_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //reverse
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Reverse Pilk " << i << std::endl;

            ts->setNeighborhoodType(reverse);
            std::string filename = "ftv170_reverse_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "ftv170_path_reverse_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //insert
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Insert Pilk " << i << std::endl;

            ts->setNeighborhoodType(insert);
            std::string filename = "ftv170_insert_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "ftv170_path_insert_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }
    }
    delete ts;
    delete graph;
}

void Test::generateFile_BestSolutionInTime_rbg358v2(int numberOfInstances, int time) {
    std::cout << "------Test rbg358.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;

    TSPGraph *graph;

    TabooSearch* ts = new TabooSearch();

    //rbg358.xml
    graph = DataReader::createGraphFromFile("rbg358.xml");
    if(graph)
    {
        std::vector<int> initSolution = graph->greedyTSP();
        ts->setGraph(graph);
        ts->setStopTime(time);

        //swap
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Swap Pilk " << i << std::endl;

            ts->setNeighborhoodType(swap);
            std::string filename = "rbg358_swap_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "rbg358_path_swap_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //reverse
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Reverse Pilk " << i << std::endl;

            ts->setNeighborhoodType(reverse);
            std::string filename = "rbg358_reverse_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "rbg358_path_reverse_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }

        //insert
        for(int i = 0; i < numberOfInstances; i++)
        {
            std::cout << "Insert Pilk " << i << std::endl;

            ts->setNeighborhoodType(insert);
            std::string filename = "rbg358_insert_" + std::to_string(i) + "_500.txt";
            std::vector<int> res = ts->runTests(500, initSolution, filename.c_str());

            std::string pathFilename = "rbg358_path_insert_" + std::to_string(i) + "_500.txt";
            DataReader::savePathToFile(res,pathFilename.c_str());

            std::cout << std::endl;
        }
    }
    delete ts;
    delete graph;
}
