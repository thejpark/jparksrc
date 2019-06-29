#include <vector>
#include <iostream>
#include <memory>

#define _USE_MATH_DEFINES
#include <math.h>

struct Point {
    Point(double a, double b) : x(a), y(b) {}
    double x, y;
};

using namespace std;

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

    double GetArea() {
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

    double GetArea() {
        return (p2.x - p1.x) * (p2.y - p1.y);
    }

private:
    Point p1, p2;
};

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

private:
    Point p1, p2, p3;
};

class AreaVisitor : public ShapeVisitor{
public:
    AreaVisitor(): total(0) {}

    double GetTotalArea() {
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

    void Reset() {
        total = 0;
    }

private:
    double total;
};


int main()
{
    vector<unique_ptr<Shape>> vs;
    vs.emplace_back(new Circle(Point(1.0, 1.0), 2));
    vs.emplace_back(new Rectangle(Point(1.0, 1.0), Point(3.0, 3.0)));
    vs.emplace_back(new Triangle(Point(1.0, 1.0), Point(3.0, 1.0), Point(2.0, 4.0)));
    AreaVisitor visitor;
    for (auto& e : vs)
    {
        e->Accept(visitor);
    }

    cout << "the result is " << visitor.GetTotalArea() << endl;
}
