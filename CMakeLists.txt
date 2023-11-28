cmake_minimum_required(VERSION 3.26)
project(PEA_Projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_Projekt2 main.cpp
        data/DataReader.cpp
        data/DataReader.h
        representations/GraphRep.cpp
        representations/GraphRep.h
        xmlParser/tinyxml2.cpp
        xmlParser/tinyxml2.h
        graph/TSPGraph.cpp
        graph/TSPGraph.h
)
