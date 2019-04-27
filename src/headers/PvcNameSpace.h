//
// Created by imoussaousmane on 05/12/2018.
//

#ifndef TEST_CPP_ALGORITHMS_H
#define TEST_CPP_ALGORITHMS_H

#include <memory>
#include <vector>
#include <list>
#include <array>
#include <iostream>
#include "Edge.h"

namespace pvc_name_space {

 const int WEIGHT_LIMIT = 50;
 const std::string PATH = "../file_generated.txt";

 /**
  * Classe générant le fichier et modélisant un graph. Elle correspond à la question 1 du sujet.
  */
 class File {

    private:
        int _numberOfNodes;
        std::vector<std::array<int, 2>> _listTuples;
        std::list<Edge<int>> _listEdges;
        std::list<int> _weightList;
        std::vector<std::vector<int>> _matrix;
        std::vector<std::array<int, 2>> getListTuples();
        void createEdges();
        void createMatrix();
        void randomNumbersGenerated();
        void writeInFile();

    public :
        File(int numberOfNodes);
        std::list<Edge<int>> getListEdges() const ;
        std::vector<std::vector<int>> getMatrix() const ;
        int getNumberOfNodes() const ;
        virtual ~File();
    };

 template<typename T,template <typename, typename = std::allocator<T>> class Container>
 bool contains(const Container<T> & containers, const T & t);

 template<typename T,template <typename, typename = std::allocator<T>> class Container>
 std::vector<T> search(const Container<T> & containers, const T &t);

 bool is_number(const std::string& value);
 std::array<std::string, 3> stringSplit(std::string value);

 double computeDistance(const Point & point1, const Point & point2);

    template<class T>
    void showList(std::list<T> list){
        std::cout << "[";
        int i = 0;
        for(const auto& el : list){
            std::cout << el;
            if(i < list.size()-1){
                std::cout << ",";
            }
            i++;
        }
        std::cout << "]";
    }
}

#endif //TEST_CPP_ALGORITHMS_H
