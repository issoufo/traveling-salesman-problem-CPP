//
// Created by imoussaousmane on 27/12/2018.
//

#ifndef TEST_CPP_EDGEPOINTGENERATOR_H
#define TEST_CPP_EDGEPOINTGENERATOR_H

#include <list>

#include "Point.h"
#include "Edge.h"

/**
 * Génère la matrice des distances à vol d'oiseau à partir d'une liste des points. Cette classe correspond à la question 7 du sujet.
 */
class EdgePointGenerator {
    private:
        const std::list<Point> _points;
        std::list<Edge<Point>> _edges;
        void edgesGenerator(std::list<Point> points);

    public:
        explicit EdgePointGenerator(std::list<Point> points);
        /**
         *
         * @return la matrice des distances à vol d'oiseau(liste des arrêtes).
         */
        std::list<Edge<Point>> coord_vers_matrice() ;
        virtual ~EdgePointGenerator();
};


#endif //TEST_CPP_EDGEPOINTGENERATOR_H
