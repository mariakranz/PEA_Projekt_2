cmake_minimum_required(VERSION 3.26)
project(PEA_Projekt2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(PEA_Projekt2 main.cpp
        data/DataReader.cpp
        data/DataReader.h
        representations/GraphRep.cpp
        representations/GraphRep.h
        xmlParser/tinyxml2.cpp
        xmlParser/tinyxml2.h
        graph/TSPGraph.cpp
        graph/TSPGraph.h
        algorithms/TabooSearch.cpp
        algorithms/TabooSearch.h
        tests/Test.cpp
        tests/Test.h
)
