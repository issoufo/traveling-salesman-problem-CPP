//
// Created by imoussaousmane on 18/02/2019.
//

#include <cmath>
#include "../headers/TwoOpt.h"
#include "../headers/PvcNameSpace.h"

TwoOpt::TwoOpt(std::list<Point> listVilles, Point depart) {
    if(listVilles.size() == 0){
        throw std::invalid_argument("Not accept empty list of elements.");
    }
    _nearestNeighbour = std::make_unique<NearestNeighbour>(listVilles, depart);
    _initialPath = _nearestNeighbour->getMinPathEdges(depart);
}

/**
 * Implémentation de l'algorithme 2-OPT. Cette implémentation est basée sur des arrêtes. Si y a permuataion des noeuds entre arrêtes,
 * on recalcule le poids des arrêtes modifiées. Par exemple si le 2ème noeud de la première arrête permute avec le 1er noeud de la 3ème arrête,
 * alors on recalcule le poids de ces arrêtes ainsi le premier et 2ème noeud de la 2ème arrête permutent aussi entre eux et son poids est aussi recalculé.
 */
void TwoOpt::improveNearestNeighbour(){
    int size = _initialPath.size();
    bool ok = true;
    while(ok){
        ok = false;
        for (int i = 0; i < size; i++) {
            std::list<Edge<Point>>::iterator itI = begin(_initialPath);
            std::advance(itI, i);

            std::list<Edge<Point>>::iterator itIPlus1 = begin(_initialPath);
            std::advance(itIPlus1, i+1);
            for (int j = i+2; j < size; j++) {
                std::list<Edge<Point>>::iterator itJ = begin(_initialPath);
                std::advance(itJ, j);

                std::list<Edge<Point>>::iterator itJMoins1 = begin(_initialPath);
                std::advance(itJMoins1, j-1);

                double oldDistance = (*itI).getWeight() + (*itJ).getWeight();
                double newDistance = computeNewDistance(*itI, *itJ);
                if (oldDistance > newDistance) {
                    Edge<Point> newEdge1((*itI).getFirstNode(), (*itJ).getFirstNode());
                    Edge<Point> newEdge2((*itI).getSecondNode(), (*itJ).getSecondNode());

                    swap(*itI, newEdge1);
                    swap((*itJ), newEdge2, false);

                    (*itIPlus1).setFirstNode((*itI).getSecondNode());
                    (*itIPlus1).setWeight();
                    (*itJMoins1).setSecondNode((*itJ).getFirstNode());
                    (*itJMoins1).setWeight();
                    ok = true;
                }
            }
        }
    }
}

void TwoOpt::swap(Edge<Point> &edge1, Edge<Point> &edge2, bool isFirstEdge) {
    if(isFirstEdge){
        edge1.setSecondNode(edge2.getSecondNode());
        edge1.setWeight();
        return;
    }
    edge1.setFirstNode(edge2.getFirstNode());
    edge1.setWeight();
}

/**
 * @description calcule la distance entre 2 arrêtes
 * @param edge1 arrête 1
 * @param edge2 arrête 2
 * @return la distance entre ces 2 arrêtes
 */
double TwoOpt::computeNewDistance(Edge<Point> & edge1, Edge<Point> & edge2){
    double distanceXiXj = pvc_name_space::computeDistance(edge1.getFirstNode(), edge2.getFirstNode());
    double distanceXiPlus1XjPlus1 = pvc_name_space::computeDistance(edge1.getSecondNode(), edge2.getSecondNode());
    return distanceXiXj + distanceXiPlus1XjPlus1;
}

/**
 * Affiche le meilleur chemin ainsi que sa distance.
 */
void TwoOpt::showBestPath() {
    improveNearestNeighbour();
    std::cout << "[";
    int i = 0;
    for(const auto & edge : _initialPath){
        std::cout << edge.getFirstNode() << ",";
        if(i == _initialPath.size()-1) {
            std::cout << edge.getSecondNode();
        }
        _distance += edge.getWeight();
        i++;
    }
    std::cout << "] : " << _distance;
}

std::pair<std::list<Edge<Point>>, double> TwoOpt::meilleure_boucle() {
    improveNearestNeighbour();
    return std::make_pair(_initialPath, _distance);
}