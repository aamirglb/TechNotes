#include <iostream>
#include <variant>
#include <vector>

struct Coord {
    Coord(double x, double y) :
    x_{x}, y_{y} {
    }
double x_;
double y_;
};

struct Line {
    Line(Coord p1, Coord p2) :
        p1_{p1}, p2_{p2} {}
    void draw() const {
        std::cout << "Drawing Line\n";
    }
Coord p1_;
Coord p2_;
};

struct Circle {
    Circle(Coord c, int r) :
    c_{c}, r_{r} {}
    void draw() const {
        std::cout << "Drawing Circle\n";
    }
Coord c_;
int r_;
};

struct Rectangle {
    Rectangle(Coord tl, Coord br) :
        tl_{tl}, br_{br} {}
    void draw() const {
        std::cout << "Drawing Rectangle\n";
    }
Coord tl_;
Coord br_;
};

// Common type of all geometric object types:
using GeoObj = std::variant<Line, Circle, Rectangle>;

// create and initialze a collection of geometric objects
std::vector<GeoObj> createFigure() {
    std::vector<GeoObj> f;
    f.push_back(Line{Coord{1, 2}, Coord{3, 4}});
    f.push_back(Circle{Coord{5, 5}, 2});
    f.push_back(Rectangle{Coord{3, 3}, Coord{6, 4}});
    return f;
}

int main() {
    std::vector<GeoObj> figure = createFigure();
    for(const GeoObj& geoobj : figure) {
        std::visit([](const auto& obj) {
            obj.draw();
        }, geoobj);
    }
}