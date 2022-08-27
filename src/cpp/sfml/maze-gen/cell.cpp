#include "cell.hpp"
#include <iostream>

void Cell::init(uint32_t w, uint32_t h, uint32_t cw, uint32_t t)
{
    m_width = w;
    m_height = h;
    m_cellWidth = cw;
    m_rows = m_height / m_cellWidth;
    m_cols = m_width / m_cellWidth;
    m_lineThickness = t;

}


Cell::Cell(sf::RenderWindow& win,
           sf::Vector2f pos,
           sf::Color color)
    : m_window {win}
    , m_position {pos.x, pos.y}
    , m_cellColor {color}
    , m_walls {true, true, true, true}
    , m_visited {false}
    , m_highlight {false}
    , m_fill {true}
{

    //
    //   (x,y)       (x,y+1)    (x,y+2)    (x,y+3)  (x,y+4)
    //    +----------+----------+----------+----------+----------+
    //    |          |          |          |          |          |
    //    |          |          |          |          |          |
    //   (x+1,y)     (x+1,y+1)  (x+1,y+2)  (x+1,y+3)  (x+1,y+4)
    //    +----------+----------+----------+----------+----------+
    //    |          |          |          |          |          |
    //    |          |          |          |          |          |
    //    +----------+----------+----------+----------+----------+
    //

    // create walls
    m_topWall.setSize   (sf::Vector2f( m_cellWidth,     m_lineThickness ));
    m_rightWall.setSize (sf::Vector2f( m_lineThickness, m_cellWidth     ));
    m_bottomWall.setSize(sf::Vector2f( m_cellWidth,     m_lineThickness ));
    m_leftWall.setSize  (sf::Vector2f( m_lineThickness, m_cellWidth     ));

    sf::Vector2f top    = {(m_position.y * m_cellWidth), (m_position.x  * m_cellWidth)};
    sf::Vector2f right  = {(m_position.y * m_cellWidth) + m_cellWidth, (m_position.x  * m_cellWidth)};
    sf::Vector2f bottom = {(m_position.y * m_cellWidth), (m_position.x  * m_cellWidth) + m_cellWidth};
    sf::Vector2f left   = {(m_position.y * m_cellWidth), (m_position.x  * m_cellWidth)};

    // setup wall position
    m_topWall.setPosition(top);
    m_rightWall.setPosition(right);
    m_bottomWall.setPosition(bottom);
    m_leftWall.setPosition(left);

    m_fillRect.setFillColor(sf::Color(128, 0, 128, 255));
    m_highlightRect.setFillColor(sf::Color(0, 255, 0, 210));
}

void Cell::draw() {

    if(m_walls.top) {
        m_window.draw(m_topWall);
    }

    if(m_walls.right) {
        m_window.draw(m_rightWall);
    }

    if(m_walls.bottom) {
        m_window.draw(m_bottomWall);
    }

    if(m_walls.left) {
        m_window.draw(m_leftWall);
    }

    if(m_visited && m_fill) {
        // remove line thickness
        auto thickness = (m_lineThickness * 2);
        auto width = m_cellWidth - thickness;
        auto height = m_cellWidth - thickness;

        // sf::Vector2f pos = { (m_position.y * m_cellWidth) + m_lineThickness, (m_position.x * m_cellWidth)+m_lineThickness};

        // if(!m_walls.left) {
        //     pos.x -= m_lineThickness;
        //     width += thickness;
        // }
        // if(!m_walls.right) {
        //     pos.x += m_lineThickness;
        //     width += thickness;
        // }

        // if(!m_walls.top) {
        //     pos.y -= m_lineThickness;
        //     height += thickness;
        // }
        // if(!m_walls.bottom) {
        //     pos.y += m_lineThickness;
        //     height += thickness;
        // }

        // std::cout << "pos: " << (m_position.x * m_cellWidth) << " " << (m_position.y * m_cellWidth) << std::endl;
        // std::cout << "new pos: " << pos.x << " " << pos.y << std::endl;
        if(m_position.x == 0 && m_position.y == 0) {
        std::cout << m_walls.top << " " << m_walls.right << " " << m_walls.bottom << " " << m_walls.left << std::endl;
        std::cout << width << " " << height << std::endl;
        }

        sf::Vector2f size = sf::Vector2f(m_cellWidth, m_cellWidth);
        sf::Vector2f pos = {(m_position.y * m_cellWidth) + m_lineThickness, (m_position.x  * m_cellWidth)+m_lineThickness};

        if(!m_walls.bottom) {
            size.y += m_lineThickness;
        }
        if(!m_walls.right) {
            size.x += m_lineThickness;
        }
        m_fillRect.setSize(size);
        m_fillRect.setPosition(pos);
        m_window.draw(m_fillRect);
    }

    if(m_highlight) {
        auto thickness = (m_lineThickness * 2);
        m_highlightRect.setSize(sf::Vector2f(m_cellWidth - m_lineThickness, m_cellWidth - m_lineThickness));
        m_highlightRect.setPosition({(m_position.y * m_cellWidth) + thickness/2, (m_position.x  * m_cellWidth) + thickness/2});
        m_window.draw(m_highlightRect);
    }
}

std::vector<sf::Vector2f> Cell::getNeighbors() {
    std::vector<sf::Vector2f> neighbors;

    if((m_position.x + 1) < m_rows) {
        neighbors.push_back({m_position.x + 1, m_position.y});
    }

    if((m_position.x - 1) >= 0) {
        neighbors.push_back({m_position.x - 1, m_position.y});
    }

    if((m_position.y + 1) < m_cols) {
        neighbors.push_back({m_position.x, m_position.y + 1});
    }

    if((m_position.y - 1) >= 0) {
        neighbors.push_back({m_position.x, m_position.y - 1});
    }
    return neighbors;
}

void Cell::reset()
{
    m_walls.top = true;
    m_walls.right = true;
    m_walls.bottom = true;
    m_walls.left = true;
    m_visited = false;
    m_highlight = false;
    m_fill = true;
}
