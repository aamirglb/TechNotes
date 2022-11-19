#include "spreedsheet.hpp"
#include "format"
#include <stdexcept>
#include <utility>

Spreedsheet::Spreedsheet(size_t width, size_t height)
    : m_width{width}
    , m_height{height}
{
    m_cells = new SpreedsheetCell*[m_width];
    for(size_t i{}; i < m_width; ++i) {
        m_cells[i] = new SpreedsheetCell[m_height];
    }
}

void Spreedsheet::setCellAt(size_t x, size_t y, const SpreedsheetCell& cell)
{
    // if(!inRange(x, m_width)) {
    //     throw std::out_of_range{ fmt::format("{} must be less than {}.", x, m_width) };
    // }

    // if(!inRange(y, m_height)) {
    //     throw std::out_of_range { fmt::format("{} must be less than {}.", y, m_height) };
    // }
    verifyCoordinate(x, y);
    m_cells[x][y] = cell;
}

SpreedsheetCell& Spreedsheet::getCellAt(size_t x, size_t y) {
    // if(!inRange(x, m_width)) {
    //     throw std::out_of_range{ fmt::format("{} must be less than {}.", x, m_width) };
    // }

    // if(!inRange(y, m_height)) {
    //     throw std::out_of_range { fmt::format("{} must be less than {}.", y, m_height) };
    // }
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

void Spreedsheet::verifyCoordinate(size_t x, size_t y) const {
    if(x >= m_width) {
        throw std::out_of_range{ fmt::format("{} must be less than {}.", x, m_width) };
    }
    if(y >= m_height) {
        throw std::out_of_range { fmt::format("{} must be less than {}.", y, m_height) };
    }
}

Spreedsheet::~Spreedsheet()
{
    for(size_t i{}; i < m_width; ++i) {
        delete[] m_cells[i];
    }
    delete [] m_cells;
    m_cells = nullptr;
}

Spreedsheet::Spreedsheet(const Spreedsheet& src)
    : Spreedsheet {src.m_width, src.m_height}  // delegating constructor
{
    for(size_t i{}; i < m_width; ++i) {
        for(size_t j{}; j < m_height; ++j) {
            m_cells[i][j] = src.m_cells[i][j];
        }
    }
}

// This is not exception safe!!
// If an exception is thrown while allocating the memory,
// then the object will be in a corrupt state!!
Spreedsheet& Spreedsheet::operator=(const Spreedsheet& rhs)
{
    if(this == &rhs) {
        return *this;
    }

    // free old memory
    for(size_t i{}; i < m_width; ++i) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;

    // Allocate new one and copy data
    m_width = rhs.m_width;
    m_height = rhs.m_height;

    m_cells = new SpreedsheetCell*[m_width];
    for(size_t i{}; i < m_width; ++i) {
        m_cells[i] = new SpreedsheetCell[m_height];
    }

    for(size_t i{}; i < m_width; ++i) {
        for(size_t j{}; j < m_height; ++j) {
            m_cells[i][j] = rhs.m_cells[i][j];
        }
    }
    return *this;
}

void Spreedsheet::swap(Spreedsheet& other) noexcept
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

void Swap(Spreedsheet& first, Spreedsheet& second) noexcept
{
    first.swap(second);
}

Spreedsheet& Spreedsheet::operator=(const Spreedsheet& rhs)
{
    // Do all work in tmp instance using copy constructor
    Spreedsheet tmp{rhs};
    swap(tmp);
    return *this;
}