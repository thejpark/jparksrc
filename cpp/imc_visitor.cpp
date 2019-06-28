#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

struct Point {
    double x, y;
};

using Area = double;

class Circle;
class Rectangle;
class Triangle;

class ShapeVisitor {
public:
    virtual ~ShapeVisitor() {}
    virtual void Visit(Circle& c) = 0;
    virtual void Visit(Rectangle& r) = 0;
    virtual void Visit(Triangle& t) = 0;
};

class Shape {
public:
    virtual ~Shape() {};
    virtual void Accept(ShapeVisitor& s) = 0;
};

class Circle : public Shape {
public:
    Circle(Point point, unsigned int radius) : p(point), r(radius) {};
    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    Area GetArea() {
        return r * r * M_PI;
    }

private:
    Point p;
    double r;
};

class Rectangle : public Shape {
public:
    Rectangle(Point lowerLeft, Point upperRight) : p1(lowerLeft), p2(upperRight) {}
    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    Area GetArea() {
        return (p2.x - p1.x) * (p2.y - p1.y);
    }

private:
    Point p1, p2;
};

class Triangle : public Shape{
public:
    Triangle();
    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    Area GetArea() {
        return 0;
    }
};

class AreaVisitor : public ShapeVisitor{
public:
    AreaVisitor(): total(0) {}
    Area GetTotalArea() {
        return total;
    }
    void Visit(Circle& c) override {
        total += c.GetArea();
    }
    void Visit(Rectangle& r) override {
        total += r.GetArea();
    }
    void Visit(Triangle& t) override {
        total += t.GetArea();
    }

private:
    Area total;
};


int main()
{
}
