#ifndef SHAPE_VISITOR_HPP
#define SHAPE_VISITOR_HPP

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
#endif
