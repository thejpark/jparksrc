#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <sstream>
#include "Shape.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "AreaVisitor.hpp"

using namespace std;

enum class Kind {circle, rectangle, triangle};
unordered_map<string, Kind> m{{"CIRCLE", Kind::circle}, {"RECTANGLE", Kind::rectangle}, {"TRIANGLE", Kind::triangle}};

unique_ptr<Shape> ReadShapes(string& s)
{
    vector<string> line;
    stringstream ss(s);
    string t;
    Shape *ptr = nullptr;

    while(getline(ss, t, ' '))
    {
        line.emplace_back(t);
    }

    switch (m[line[0]])
    {
    case Kind::circle:
        ptr = Circle::create(line);
        break;

    case Kind::rectangle:
        ptr = Rectangle::create(line);
        break;

    case Kind::triangle:
        ptr = Triangle::create(line);
        break;

    default:
        break;
    }

    return unique_ptr<Shape>(ptr);
}

// exmaple run:
// $a.out[enter]
// CIRCLE 1.0 1.0 2.0[enter]
// RECTANGLE 1.0 1.0 3.0 3.0[enter]
// [Ctrl-d]
// total area: 16.5664
// $_
int main()
{
    vector<unique_ptr<Shape>> vs;
    string s;
    while (getline(cin, s))
    {
        vs.emplace_back(ReadShapes(s));
    }

    AreaVisitor visitor;
    for (auto& e : vs)
    {
        e->Accept(visitor);
    }

    cout << "total area: " << visitor.GetTotalArea() << endl;
}
