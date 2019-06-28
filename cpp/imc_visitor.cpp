#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    Circle();
    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    size_t GetArea() {
        return 0;
    }
};

class Rectangle : public Shape {
public:
    Rectangle();
    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    size_t GetArea() {
        return 0;
    }
};

class Triangle : public Shape{
public:
    Triangle();
    void Accept(ShapeVisitor& visitor) override {
        visitor.Visit(*this);
    }

    size_t GetArea() {
        return 0;
    }
};

class AreaVisitor : public ShapeVisitor{
public:
    AreaVisitor(): total(0) {}
    size_t GetTotalArea() {
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
    size_t total;
};


int main()
{
}
