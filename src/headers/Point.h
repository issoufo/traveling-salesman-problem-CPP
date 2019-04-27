//
// Created by imoussaousmane on 24/12/2018.
//

#ifndef TEST_CPP_POINT_H
#define TEST_CPP_POINT_H


#include <ostream>

class Point {
private:
    int  _x;
    int  _y;
public:
    explicit Point(int x, int y);
    int getX() const;
    int getY() const;
    Point & operator=(const Point & point);
    bool operator==(const Point & point) const ;
    bool operator!=(const Point & point) const ;
    friend bool operator<(const Point & point1, const Point & point2);
    friend std::ostream & operator<<(std::ostream & os, const Point & point);
    virtual ~Point();
};


#endif //TEST_CPP_POINT_H
