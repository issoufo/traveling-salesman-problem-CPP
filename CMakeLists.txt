cmake_minimum_required(VERSION 3.12)
project(test_cpp)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp src/cpps/PvcNameSpace.cpp src/headers/PvcNameSpace.h src/headers/Edge.h src/headers/Graph.h src/headers/Permutation.h src/cpps/Point.cpp src/headers/Point.h src/headers/LoopGenerator.h src/headers/Boucle.h src/headers/Boucle.h src/headers/DistanceGenerator.h src/cpps/EdgePointGenerator.cpp src/headers/EdgePointGenerator.h src/headers/NearestNeighbour.h src/cpps/NearestNeighbour.cpp src/cpps/TwoOpt.cpp src/headers/TwoOpt.h src/cpps/GeneticAlgorithm.cpp src/headers/GeneticAlgorithm.h)

add_executable(test_cpp ${SOURCE_FILES})