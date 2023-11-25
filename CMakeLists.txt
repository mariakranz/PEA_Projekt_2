cmake_minimum_required(VERSION 3.26)
project(PEA_Projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_Projekt2 main.cpp
        data/DataReader.cpp
        data/DataReader.h
        graphs/Graph.cpp
        graphs/Graph.h
        graphs/DirectedGraph.cpp
        graphs/DirectedGraph.h
        representations/GraphRep.cpp
        representations/GraphRep.h)
