//
// Created by imoussaousmane on 18/02/2019.
//

#ifndef TEST_CPP_TWOOPT_H
#define TEST_CPP_TWOOPT_H


#include "NearestNeighbour.h"

/**
 * 2-OPT. Elle correspond à la question 10 du sujet.
 */
class TwoOpt {

    private:
        std::unique_ptr<NearestNeighbour> _nearestNeighbour;
        std::list<Edge<Point>> _initialPath;
        double _distance = 0.0;
        void swap(Edge<Point> & edge1, Edge<Point> & edge2, bool isFirstEdge = true) ;
        double computeNewDistance(Edge<Point> & edge1, Edge<Point> & edge2);

    public:
        explicit TwoOpt(std::list<Point> listVilles, Point depart);
        void improveNearestNeighbour();
        void showBestPath() ;
        std::pair<std::list<Edge<Point>>, double> meilleure_boucle() ;
};


#endif //TEST_CPP_TWOOPT_H
