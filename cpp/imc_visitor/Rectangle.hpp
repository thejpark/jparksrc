#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"
#include "ShapeVisitor.hpp"
#include <vector>
#include <string>

using namespace std;

class Rectangle : public Shape {
public:
    Rectangle(Point lowerLeft, Point upperRight) : p1(lowerLeft), p2(upperRight) {}

    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    double GetArea() {
        return (p2.x - p1.x) * (p2.y - p1.y);
    }

    static Rectangle* create(vector<string>& v)
    {
        double x1 = stod(v[1]);
        double y1 = stod(v[2]);
        double x2 = stod(v[3]);
        double y2 = stod(v[4]);
        return new Rectangle(Point(x1, y1), Point(x2, y2));
    }

private:
    Point p1, p2;
};
#endif
