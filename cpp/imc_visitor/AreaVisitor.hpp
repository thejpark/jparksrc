#ifndef AREA_VISITOR_HPP
#define AREA_VISITOR_HPP

#include "ShapeVisitor.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"

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
#endif
