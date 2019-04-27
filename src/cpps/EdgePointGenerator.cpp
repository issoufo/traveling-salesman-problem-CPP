//
// Created by imoussaousmane on 27/12/2018.
//

#include <cmath>
#include "../headers/EdgePointGenerator.h"

EdgePointGenerator::EdgePointGenerator(std::list<Point> points): _points(points) {
    if(points.empty() or points.size() < 2){
        throw std::invalid_argument("List of points must contains at least 2 points.");
    }
    edgesGenerator(points);
}

void EdgePointGenerator::edgesGenerator(std::list<Point> points) {
    for (const auto & point1 : points) {
        for (const auto & point2 : points) {
            if(point1 != point2){
                double computeDistance = std::pow((point2.getX() - point1.getX()), 2) + std::pow((point2.getY() - point1.getY()), 2);
                double distance = std::sqrt(computeDistance);

                Edge<Point> edge(point1, point2, distance);
                _edges.push_back(edge);
            }
        }
    }
}

EdgePointGenerator::~EdgePointGenerator() {}

std::list<Edge<Point>> EdgePointGenerator::coord_vers_matrice() {
    return _edges;
}
