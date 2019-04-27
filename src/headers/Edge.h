//
// Created by imoussaousmane on 06/12/2018.
//

#ifndef TEST_CPP_EDGE_H
#define TEST_CPP_EDGE_H

#include <cmath>
#include "Point.h"

template<typename T>
class Edge {
    private:
        T _firstNode;
        T _secondNode;
        double _weight;

    public:
        explicit Edge(T firstNode, T secondNode, double weight = 0.0): _firstNode(firstNode), _secondNode(secondNode), _weight(weight){}

        T getFirstNode() const{
            return _firstNode;
        }

        T getSecondNode() const{
            return _secondNode;
        }

        double getWeight() const{
            return _weight;
        }

        void setFirstNode(const T & t) {
            _firstNode = t;
        }

        void setSecondNode(const T & t) {
            _secondNode = t;
        }

        void setWeight() {
            if (std::is_convertible<T, Point>::value) {
                double computeDistance = std::pow((_secondNode.getX() - _firstNode.getX()), 2) + std::pow((_secondNode.getY() - _firstNode.getY()), 2);
                double distance = std::sqrt(computeDistance);
                _weight = distance;
            }
        }

        bool operator==(const Edge & edge) const {
            return (_firstNode == edge._firstNode && _secondNode == edge._secondNode) || (_firstNode == edge._secondNode && _secondNode==edge._firstNode);
        }

        bool operator!=(const Edge & edge) const {
            return !operator==(edge);
        }

        friend bool operator<(const Edge & edge1, const Edge & edge2) {
            return edge1._weight < edge2._weight;
        }

        friend std::ostream & operator<<(std::ostream & os, const Edge<T> & edge){
            os << "["  << edge._firstNode << " " << edge._secondNode << "] : distance = " << edge._weight << std::endl;
            return os;
        }

        virtual ~Edge(){};
};


#endif //TEST_CPP_EDGE_H
