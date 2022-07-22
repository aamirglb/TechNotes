#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "settings.hpp"

class Cell {
public:
    using CellPtr = std::shared_ptr<Cell>;
    struct WallType {
        bool top;
        bool right;
        bool bottom;
        bool left;
    };

    static void init(uint32_t w, uint32_t h, uint32_t cw, uint32_t t);

    Cell(sf::RenderWindow& win,
        sf::Vector2f pos = sf::Vector2f{0, 0},
        sf::Color color = sf::Color::Blue);

    void setTopWall   (bool top)        { m_walls.top = top; }
    void setRightWall (bool right)      { m_walls.right = right; }
    void setBottomWall(bool bottom)     { m_walls.bottom = bottom; }
    void setLeftWall  (bool left)       { m_walls.left = left; }
    void setHighlight (bool highlight)  { m_highlight = highlight; }
    void setVisited   (bool visited)    { m_visited = visited; }
    bool getVisited   () const noexcept { return m_visited; }
    void setFill      (bool fill)       { m_fill = fill; }
    sf::Vector2f getPosition() const noexcept { return m_position; }

    void draw();
    std::vector<sf::Vector2f> getNeighbors();
    void reset();

private:
    static inline uint32_t              m_width;
    static inline uint32_t              m_height;
    static inline uint32_t              m_cellWidth;
    static inline uint32_t              m_rows;
    static inline uint32_t              m_cols;
    static inline uint32_t              m_lineThickness;

private:
    sf::RenderWindow&     m_window;
    sf::Vector2f          m_position;
    sf::Color             m_cellColor;
    WallType              m_walls;
    bool                  m_visited;
    bool                  m_highlight;
    bool                  m_fill;

    sf::RectangleShape    m_topWall;
    sf::RectangleShape    m_rightWall;
    sf::RectangleShape    m_bottomWall;
    sf::RectangleShape    m_leftWall;

    sf::RectangleShape    m_fillRect;
    sf::RectangleShape    m_highlightRect;

};
