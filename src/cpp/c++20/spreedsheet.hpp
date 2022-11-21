#pragma once
#include <cstddef>
#include "spreedsheetcell.hpp"

class Spreedsheet
{
public:
    Spreedsheet(size_t width, size_t height);
    ~Spreedsheet();
    Spreedsheet(const Spreedsheet& src);
    Spreedsheet& operator=(const Spreedsheet& rhs);

    void swap(Spreedsheet& other) noexcept;

    void setCellAt(size_t x, size_t y, const SpreedsheetCell& cell);
    SpreedsheetCell& getCellAt(size_t x, size_t y);
private:
    // bool inRange(size_t value, size_t upper) const;
    void verifyCoordinate(size_t x, size_t y) const;

private:
    size_t            m_width{};
    size_t            m_height;
    SpreedsheetCell** m_cells{};
};

void swap(Spreedsheet& first, Spreedsheet& second) noexcept;