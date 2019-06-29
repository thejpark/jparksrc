#ifndef SHAPE_HPP
#define SHAPE_HPP

class ShapeVisitor;

class Shape {
public:
    virtual ~Shape() {};
    virtual void Accept(ShapeVisitor& s) = 0;
};

struct Point {
    Point(double a, double b) : x(a), y(b) {}
    double x, y;
};
#endif
