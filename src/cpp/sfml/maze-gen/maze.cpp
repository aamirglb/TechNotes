#include "maze.hpp"
#include <random>
#include <iostream>

Maze::Maze(sf::RenderWindow& win, Settings& settings)
    : m_window{win}
    , m_settings{settings}
    , m_totalMoves{0}
{
    // Read appliation settings
    m_width = std::stoi(m_settings.getValue("winWidth"));
    m_height = std::stoi(m_settings.getValue("winHeight"));
    m_cellWidth = std::stoi(m_settings.getValue("cellWidth"));
    uint32_t thickness = std::stoi(m_settings.getValue("thickness"));

    m_rows = m_height / m_cellWidth;
    m_cols = m_width / m_cellWidth;

    m_totalCells = m_rows * m_cols;
    // std::cout << "rows: " << m_rows << " cols: " << m_cols << std::endl;

    // create grid of cells as single dimension vector
    //
    //  rows = 2  cols = 5
    //
    //  +--------+--------+--------+--------+--------+
    //  | (0, 0) | (0, 1) | (0, 2) | (0, 3) | (0, 4) |
    //  |   0    |   1    |   2    |   3    |   4    |
    //  +--------+--------+--------+--------+--------+
    //  | (1, 0) | (1, 1) | (1, 2) | (1, 3) | (1, 4) |
    //  |   5    |   6    |   7    |   8    |   9    |
    //  +--------+--------+--------+--------+--------+
    //  | (2, 0) | (2, 1) | (2, 2) | (2, 3) | (2, 4) |
    //  |   10   |   11   |   12   |   13   |   14   |
    //  +--------+--------+--------+--------+--------+
    //
    //  To get index based on (x, y) coordinates where x = row, y = col, use the formula
    //  index = (x * cols) + y
    //  (1, 2) => (1 * 5) + 2 = 7
    //  (2, 4) => (2 * 5) + 4 = 14
    //

    // Initiaize cell static data
    Cell::init(m_width, m_height, m_cellWidth, thickness);

    for(uint32_t i = 0; i < m_rows; ++i) {
        for(uint32_t j = 0; j < m_cols; ++j) {
            m_grid.push_back( std::make_shared<Cell>(m_window, sf::Vector2f(i, j)) );
        }
    }

    // set (0, 0) cell as current
    m_current = m_grid[0];
    m_current->setVisited(true);
    m_current->setHighlight(true);
}


CellPtr Maze::getNextCell() {
    std::vector<CellPtr> neighbors;

    // get the surrounding indices of current cell
    std::vector<sf::Vector2f> neighborsPos = m_current->getNeighbors();

    // for each neighboring cell, get the grid index
    for(auto pos : neighborsPos) {
        auto index = (pos.x * m_cols) + pos.y;
        auto cell = m_grid[ index ];

        // if cell is not visited yet, then make it eligible neighbor to visit
        if(!cell->getVisited())
            neighbors.push_back(m_grid[ index ]);
    }

    // if current cell has any unvisited neighbors
    if(neighbors.size() > 0) {
        // return a random neighbor
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (neighbors.begin(), neighbors.end(), std::default_random_engine(seed));
        return neighbors[0];
    } else {
        // current cell has no unvisited neighbor
        return nullptr;
    }
}

void Maze::removeWalls(CellPtr curr, CellPtr next) {
    auto currPos = curr->getPosition();
    auto nextPos = next->getPosition();
    // x => rows, y => cols, so x represent top/bottom walls, y represent left/right walls
    auto x = currPos.x - nextPos.x;
    auto y = currPos.y - nextPos.y;

    if(x == 1) {
        curr->setTopWall(false);
        next->setBottomWall(false);
    } else if(x == -1) {
        curr->setBottomWall(false);
        next->setTopWall(false);
    }

    if(y == 1) {
        curr->setLeftWall(false);
        next->setRightWall(false);
    } else if(y == -1) {
        curr->setRightWall(false);
        next->setLeftWall(false);
    }
}

void Maze::update()
{
    // static int test = 0;
    // ++test;
    // if(test > 5) return;
    auto nextCell = getNextCell();
    // return;
    // if current cell has unvisited neighbor
    if(nextCell != nullptr) {
        nextCell->setVisited(true);
        m_stack.push(m_current);
        m_current->setHighlight(false);
        removeWalls(m_current, nextCell);
        m_current = nextCell;
        m_current->setHighlight(true);
        ++m_totalMoves;
    } else {
        // backtrack - check if previous cell has any unvisited neighbor
        if(!m_stack.empty()) {
            m_current->setHighlight(false);
            auto cell = m_stack.top();
            m_stack.pop();
            m_current = cell;
            m_current->setHighlight(true);
            ++m_totalMoves;
        }
    }
}

void Maze::draw()
{
    for(auto cell : m_grid) {
        cell->draw();
    }
}

std::string Maze::getStats() const
{
    auto visited = std::count_if(m_grid.begin(),
                                m_grid.end(),
                                [](auto cell){
                                    return cell->getVisited();
                                });
    return std::to_string(visited)
           + "/"
           + std::to_string(m_totalCells)
           + "     Moves:  "
           + std::to_string(m_totalMoves);
}

void Maze::reset()
{
    while(!m_stack.empty()) m_stack.pop();
    for(auto cell : m_grid) {
        cell->reset();
        // cell->draw();
    }
    m_totalMoves = 0;
    m_current = m_grid[0];
    m_current->setVisited(true);
    m_current->setHighlight(true);
}

void Maze::setFill(bool fill) {
    for(auto cell : m_grid) {
        cell->setFill(fill);
    }
}

void Maze::showTracer(bool show) {
    if(m_stack.empty()) {
        m_current->setHighlight(show);
    }
}
