#include "format"

class Point {
public:
    Point(int x, int y) : m_x{x}, m_y{y} {}
    friend void DisplayPoint(const Point& p);
private:
    int m_x;
    int m_y;
};

void DisplayPoint(const Point& p) {
    fmt::print("[{}, {}]\n", p.m_x, p.m_y);
}

int main()
{
    Point p1{4, 5};
    DisplayPoint(p1);
}

