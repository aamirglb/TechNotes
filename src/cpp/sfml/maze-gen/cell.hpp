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

    Cell(sf::RenderWindow& win,
         Settings&  m_settings,
        sf::Vector2f pos = sf::Vector2f{0, 0},
        sf::Color color = sf::Color::Blue);

    void setTopWall   (bool top)        { m_walls.top = top; }
    void setRightWall (bool right)      { m_walls.right = right; }
    void setBottomWall(bool bottom)     { m_walls.bottom = bottom; }
    void setLeftWall  (bool left)       { m_walls.left = left; }
    void setHighlight (bool highlight)  { m_highlight = highlight; }
    void setVisited   (bool visited)    { m_visited = visited; }
    bool getVisited   () const noexcept { return m_visited; }
    sf::Vector2f getPosition() const noexcept { return m_position; }

    void draw();
    std::vector<sf::Vector2f> getNeighbors();

private:
    sf::RenderWindow&     m_window;
    Settings&             m_settings;
    uint32_t              m_width;
    uint32_t              m_height;
    uint32_t              m_cellWidth;
    uint32_t              m_rows;
    uint32_t              m_cols;
    // uint32_t              m_cellWidth;
    uint32_t              m_lineThickness;
    sf::Vector2f          m_position;
    sf::Color             m_cellColor;
    WallType              m_walls;
    bool                  m_visited;
    bool                  m_highlight;
    sf::RectangleShape    m_shape;
};
