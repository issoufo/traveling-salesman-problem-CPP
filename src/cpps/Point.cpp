//
// Created by imoussaousmane on 24/12/2018.
//

#include "../headers/Point.h"

Point::Point(int x, int y): _x(x), _y(y) {}

Point::~Point() {}

int Point::getX() const {
    return _x;
}

int Point::getY() const {
    return _y;
}

Point & Point::operator=(const Point & point) {
    if(this != &point){
        _x = point._x;
        _y = point._y;
    }
    return *this;
}

bool Point::operator==(const Point & point) const {
    return _x == point._x && _y == point._y;
}

bool Point::operator!=(const Point & point) const {
    return !operator==(point);
}

bool operator<(const Point & point1, const Point & point2) {
    return point1._x + point1._y < point2._x + point2._y;
}

std::ostream& operator<<(std::ostream &os, const Point &point) {
    os << "(" << point._x << "," <<point._y <<")";
    return os;
}


