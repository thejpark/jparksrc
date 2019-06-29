#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"
#include "ShapeVisitor.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <string>

using namespace std;

class Circle : public Shape {
public:
    Circle(Point point, unsigned int radius) : p(point), r(radius) {};

    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    double GetArea() {
        return r * r * M_PI;
    }

    static Circle* create(vector<string>& v)
    {
        double x = stod(v[1]);
        double y = stod(v[2]);
        double radius = stod(v[3]);
        return new Circle(Point(x, y), radius);
    }

private:
    Point p;
    double r;
};
#endif
