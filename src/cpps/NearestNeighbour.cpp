//
// Created by imoussaousmane on 17/02/2019.
//

#include <cmath>
#include "../headers/NearestNeighbour.h"

NearestNeighbour::NearestNeighbour(std::list<Point> listVilles, Point depart): _listVilles(listVilles), _listVillesCopy(listVilles), _depart(depart) {}

/**
 * @description implémentation de l'algorithme du plus proche voisin.
 * @param depart point de départ
 * @return le meilleur chemin.
 */
std::list<Edge<Point>> NearestNeighbour::getMinPathEdges(const Point & depart) {
    if (_listVillesCopy.size() == 1){
        double computeDistance = std::pow((_depart.getX() - depart.getX()), 2) + std::pow((_depart.getY() - depart.getY()), 2);
        double distance = std::sqrt(computeDistance);
        Edge<Point> edge(depart, _depart, distance);
        _result.push_back(edge);
        _distance += edge.getWeight();
        _listVillesCopy.remove(depart);
        return _result;
    }

    _listVillesCopy.remove(depart);
    _listVillesCopy.push_front(depart);
    std::set<Edge<Point>> edges = {};
    for(const auto & point : _listVillesCopy){
        if(depart != point){
            double computeDistance = std::pow((point.getX() - depart.getX()), 2) + std::pow((point.getY() - depart.getY()), 2);
            double distance = std::sqrt(computeDistance);
            Edge<Point> edge(depart, point, distance);
            edges.insert(edge);
        }
    }
    _listVillesCopy.remove(depart);
    std::set<Edge<Point>>::const_iterator it = std::next(cbegin(edges), 0);
    _result.push_back(*it);
    _distance += (*it).getWeight();
    return getMinPathEdges((*it).getSecondNode());
}

std::list<Point> NearestNeighbour::getListVilles() const {
    return _listVilles;
}

Point NearestNeighbour::getDepart() const {
    return  _depart;
}

double NearestNeighbour::getDistance() const {
    return _distance;
}

/**
 * Affiche le meilleur chemin et sa distance.
 */
void NearestNeighbour::showBestPath() {
    std::list<Edge<Point>> meilleurChemin = getMinPathEdges(_depart);
    std::cout << "[";
    for(const auto & edge : meilleurChemin){
        std::cout << edge.getFirstNode() << ",";
    }
    std::cout << _depart << "] : " << _distance;
}

/**
 *
 * @return meilleur chemin avec sa longueur.
 */
std::pair<std::list<Edge<Point>>, double>  NearestNeighbour::meilleure_boucle() {
    std::list<Edge<Point>> meilleurChemin = getMinPathEdges(_depart);
    return std::make_pair(meilleurChemin, _distance);
}