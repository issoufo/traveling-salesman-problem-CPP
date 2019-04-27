//
// Created by imoussaousmane on 07/12/2018.
//

#ifndef TEST_CPP_GRAPH_H
#define TEST_CPP_GRAPH_H
#include <utility>
#include <list>
#include <ostream>
#include <iostream>
#include "PvcNameSpace.h"
#include "EdgePointGenerator.h"
#include "DistanceGenerator.h"

/**
 * @description graphe des éléments
 * @tparam T type d'éléments
 */
template<typename T>
class Graph {

    private:
        std::unique_ptr<pvc_name_space::File> _file = nullptr;
        std::unique_ptr<DistanceGenerator<T>> _distanceGenerator = nullptr;
        std::unique_ptr<EdgePointGenerator> _edgePointGenerator = nullptr;
        std::list<T> _points;

    public:
        explicit Graph(const T & numberOfNodes, const T & depart){
            if(numberOfNodes <= 0){
                throw std::invalid_argument("Not accep value <= 0.");
            }
            _file = std::make_unique<pvc_name_space::File>(pvc_name_space::File(numberOfNodes));
            _distanceGenerator = std::make_unique<DistanceGenerator<T>>(numberOfNodes, depart, _file -> getListEdges());
        }

        explicit Graph(std::list<T> points, T depart): _points(points){
            if(points.size() == 0){
                throw std::invalid_argument("Not accep empty list of elements.");
            }
            _edgePointGenerator = std::make_unique<EdgePointGenerator>(EdgePointGenerator(points));
            _distanceGenerator = std::make_unique<DistanceGenerator<T>>(points, depart, _edgePointGenerator -> coord_vers_matrice());
        }

        /**
         *
         * @return la matrice des sommets(ints) liés
         */
        std::list<Edge<int>> getListEdges() const {
            return _file -> getListEdges();
        }

        /**
         * @return la matrice des sommets(Points)
         */
        std::list<Edge<Point>> coord_vers_matrice() const {
            return _edgePointGenerator -> coord_vers_matrice();
        }

        /**
         *
         * @return la matrice complete entre tous les sommets
         */
        std::vector<std::vector<int>> getMatrix() const {
            return _file -> getMatrix();
        }

        /**
         *
         * @return toutes les permutations
         */
        std::list<std::list<T>> genere_permutations(){
            return _distanceGenerator -> genere_permutations();
        }

        /**
         *
         * @return toutes les boucles
         */
        std::list<std::list<T>> genere_boucle(){
            return _distanceGenerator -> genere_boucle();
        }

        /**
         *
         * @return chaque boucle associée à sa distance
         */
        std::set<Boucle<T>> distances_boucles(){
            return _distanceGenerator -> distances_boucles();
        }

        /**
         * Affiche le meilleur chemin en mode console. Elle correspond à la question 6 du sujet.
         */
        void showBestPath(){
            Boucle<T> boucle = _distanceGenerator -> meilleure_boucle();
            std::cout << boucle << std::endl;
        }

        std::pair<std::list<Edge<T>>, double> meilleure_boucle(){
            std::pair<std::list<Edge<T>>, double> bestPath;
            std::list<Edge<T>> edges;
            Boucle<T> boucle = _distanceGenerator -> meilleure_boucle();
            std::list<T> elements = boucle.getElements();
            int nbreElements = elements.size();
            for(int i= 0; i < nbreElements-1; i++) {
                typename std::list<T>::const_iterator it1 = cbegin(elements);
                typename std::list<T>::const_iterator it2 = cbegin(elements);
                std::advance(it1, i);
                std::advance(it2, i + 1);
                Edge<T> edge(*it1, *it2);
                edge.setWeight();
                edges.push_back(edge);
            }

            bestPath = std::make_pair(edges, boucle.getDistance());
            return bestPath;
        }

        friend std::ostream & operator<<(std::ostream &os, const Graph<T> & graph) {
            if(std::is_convertible<T, int>::value){
                for (Edge<int> edge : graph._file -> getListEdges()) {
                    os << edge;
                }
            }

            if(std::is_convertible<T, Point>::value){
                for (Edge<Point> edge : graph._edgePointGenerator -> coord_vers_matrice()) {
                    os << edge;
                }
            }

            return os;
        }

        virtual ~Graph(){}

};

#endif //TEST_CPP_GRAPH_H
