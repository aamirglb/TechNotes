#include "cell.hpp"
#include <iostream>

Cell::Cell(sf::RenderWindow& win,
           Settings&  settings,
           sf::Vector2f pos,
           sf::Color color)
    : m_window {win}
    , m_settings {settings}
    , m_position {pos.x, pos.y}
    , m_cellColor {color}
    , m_walls {true, true, true, true}
    , m_visited {false}
    , m_highlight {false}
{
    m_width = std::stoi(m_settings.getValue("winWidth"));
    m_height = std::stoi(m_settings.getValue("winHeight"));
    m_cellWidth = std::stoi(m_settings.getValue("cellWidth"));
    m_rows = m_height / m_cellWidth;
    m_cols = m_width / m_cellWidth;
    m_lineThickness = std::stoi(m_settings.getValue("thickness"));
}

void Cell::draw() {
    if(m_walls.top) {
        // x -> move horizontal (row)
        // y -> moves vertical (col)
        sf::RectangleShape topLine(sf::Vector2f(m_cellWidth, m_lineThickness));
        topLine.setPosition({(m_position.y * m_cellWidth), (m_position.x  * m_cellWidth)});
        m_window.draw(topLine);
    }

    if(m_walls.right) {
        sf::RectangleShape rightLine(sf::Vector2f(m_lineThickness, m_cellWidth));
        rightLine.setPosition({(m_position.y * m_cellWidth) + m_cellWidth, (m_position.x  * m_cellWidth)});
        m_window.draw(rightLine);

    }

    if(m_walls.bottom) {
        sf::RectangleShape bottomLine(sf::Vector2f(m_cellWidth, m_lineThickness));
        bottomLine.setPosition({(m_position.y * m_cellWidth), (m_position.x  * m_cellWidth) + m_cellWidth});
        m_window.draw(bottomLine);
    }

    if(m_walls.left) {
        sf::RectangleShape leftLine(sf::Vector2f(m_lineThickness, m_cellWidth));
        leftLine.setPosition({(m_position.y * m_cellWidth), (m_position.x  * m_cellWidth)});
        m_window.draw(leftLine);
    }

    if(m_visited) {
        int width = m_cellWidth - 2;
        int height = m_cellWidth - 2;
        sf::Vector2f pos = { (m_position.y * m_cellWidth)+2, (m_position.x * m_cellWidth)+2};
        if(!m_walls.left) {
            pos.x -= 1;
            width++;
        }
        if(!m_walls.right) {
            pos.x += 1;
            width++;
        }
        if(!m_walls.top) {
            pos.y -= 1;
            height++;
        }
        if(!m_walls.bottom) {
            pos.y += 1;
            height++;
        }

        sf::RectangleShape rect(sf::Vector2f(width, height));
        rect.setPosition(pos);

        rect.setFillColor(sf::Color(128, 0, 128, 255));
        m_window.draw(rect);
    }

    if(m_highlight) {
        std::cout << m_position.x << " " << m_position.y << std::endl;
        sf::RectangleShape rect(sf::Vector2f(m_cellWidth - 2, m_cellWidth - 2));
        rect.setPosition({(m_position.y * m_cellWidth) + 1, (m_position.x  * m_cellWidth) + 1});
        rect.setFillColor(sf::Color(0, 255, 0, 210));
        m_window.draw(rect);
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
