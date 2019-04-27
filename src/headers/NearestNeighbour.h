//
// Created by imoussaousmane on 16/02/2019.
//

#include "Graph.h"
#include "Edge.h"

#ifndef TEST_CPP_NEARESTNEIGHBOUR_H
#define TEST_CPP_NEARESTNEIGHBOUR_H

#endif //TEST_CPP_NEARESTNEIGHBOUR_H

/**
 * Plus proche voisin. Elle correspon à la Question 9 du sujet
 */
class  NearestNeighbour{

    private:
        std::list<Point> _listVilles;
        std::list<Point> _listVillesCopy;
        std::list<Edge<Point>> _result = {};
        Point _depart;
        double _distance;

    public:
        explicit NearestNeighbour(std::list<Point> listVilles, Point depart);
        std::list<Point> getListVilles() const ;
        Point getDepart() const ;
        double getDistance() const ;
        std::list<Edge<Point>> getMinPathEdges(const Point &depart);
        std::pair<std::list<Edge<Point>>, double> meilleure_boucle() ;
        void showBestPath() ;
};