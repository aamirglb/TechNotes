#include "maze.hpp"
#include <random>
#include <iostream>

Maze::Maze(sf::RenderWindow& win, Settings& settings)
    : m_window{win}
    , m_settings{settings}
{
    m_width = std::stoi(m_settings.getValue("winWidth"));
    m_height = std::stoi(m_settings.getValue("winHeight"));
    m_cellWidth = std::stoi(m_settings.getValue("cellWidth"));
    m_rows = m_height / m_cellWidth;
    m_cols = m_width / m_cellWidth;
    std::cout << "rows: " << m_rows << " cols: " << m_cols << std::endl;
    for(uint32_t i = 0; i < m_rows; ++i) {
        for(uint32_t j = 0; j < m_cols; ++j) {
            std::cout << i << " " << j << std::endl;
            m_grid.push_back( std::make_shared<Cell>(m_window, m_settings, sf::Vector2f(i, j)) );
        }
    }

    m_current = m_grid[0];
    // std::cout << "curr pos: " << m_current->getPosition().x << " " << m_current->getPosition().y << std::endl;
    m_current->setVisited(true);
    m_current->setHighlight(true);
}

CellPtr Maze::getNextCell() {
    // std::vector<sf::Vector2f> neighborsPos;
    auto neighborsPos = m_current->getNeighbors();

    std::vector<CellPtr> neighbors;

    std::cout << "neighbours: ";
    for(auto pos : neighborsPos) {
        auto index = (m_cols * pos.x) + pos.y;
        std::cout << pos.x << ", " << pos.y << " => " << index << " ";
        auto cell = m_grid[ index ];
        if(!cell->getVisited())
            neighbors.push_back(m_grid[ index ]);
    }
    std::cout << std::endl;

    if(neighbors.size() > 0) {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (neighbors.begin(), neighbors.end(), std::default_random_engine(seed));
        return neighbors[0];
    } else {
        return nullptr;
    }
}

void Maze::removeWalls(CellPtr curr, CellPtr next) {
    auto currPos = curr->getPosition();
    auto nextPos = next->getPosition();
    auto x = currPos.x - nextPos.x;
    auto y = currPos.y - nextPos.y;

    if(y == 1) {
        curr->setLeftWall(false);
        next->setRightWall(false);
    } else if(y == -1) {
        curr->setRightWall(false);
        next->setLeftWall(false);
    }


    if(x == 1) {
        curr->setTopWall(false);
        next->setBottomWall(false);
    } else if(x == -1) {
        curr->setBottomWall(false);
        next->setTopWall(false);
    }
}

void Maze::update()
{
    auto nextCell = getNextCell();
    if(nextCell != nullptr) {
        nextCell->setVisited(true);
        m_stack.push(m_current);
        m_current->setHighlight(false);
        removeWalls(m_current, nextCell);
        m_current = nextCell;
        m_current->setHighlight(true);
    } else {
        if(!m_stack.empty()) {
            m_current->setHighlight(false);
            auto cell = m_stack.top();
            m_stack.pop();
            m_current = cell;
            m_current->setHighlight(true);
        }
    }
}

void Maze::draw()
{
    for(auto cell : m_grid) {
        cell->draw();
    }
}
