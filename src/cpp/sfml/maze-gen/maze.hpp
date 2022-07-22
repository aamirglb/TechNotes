#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

#include "settings.hpp"
#include "cell.hpp"

using CellPtr = std::shared_ptr<Cell>;

// Maze class for creating the grid of cells
class Maze
{
public:
    Maze(sf::RenderWindow& win, Settings& settings);
    CellPtr getNextCell();
    void removeWalls(CellPtr curr, CellPtr next);
    void update();
    void draw();
    std::string getStats() const;
    void reset();

private:
    sf::RenderWindow&     m_window;
    Settings&             m_settings;
    uint32_t              m_width;
    uint32_t              m_height;
    uint32_t              m_cellWidth;
    uint32_t              m_rows;
    uint32_t              m_cols;
    uint32_t              m_totalCells;
    std::vector<CellPtr>  m_grid;
    CellPtr               m_current;
    std::stack<CellPtr>   m_stack;
};
