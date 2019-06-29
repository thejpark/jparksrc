#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"
#include "ShapeVisitor.hpp"
#include <vector>
#include <string>

using namespace std;

class Triangle : public Shape {
public:
    Triangle(Point point1, Point point2, Point point3) : p1(point1), p2(point2), p3(point3) {}

    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    double GetArea() {
        // refer to: http://www.mathguru.com/level2/application-of-coordinate-geometry-2007101600011139.aspx
        double area = fabs((p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y) ) / 2;
        return area;
    }

    static Triangle* create(vector<string>& v)
    {
        double x1 = stod(v[1]);
        double y1 = stod(v[2]);
        double x2 = stod(v[3]);
        double y2 = stod(v[4]);
        double x3 = stod(v[5]);
        double y3 = stod(v[6]);
        return new Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3));
    }

private:
    Point p1, p2, p3;
};
#endif
