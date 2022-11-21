#include "format"
#include <optional>
#include <vector>
#include <stdexcept>

template <typename T>
class Grid
{
public:
    explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);
    virtual ~Grid() = default;

    // Explicitly default copy constructor and assignment operator
    Grid(const Grid& src) = default;
    Grid& operator=(const Grid& rhs) = default;
    // Grid<T>& operator=(const Grid<T>& rhs) = default => same as above


    // Explicitly default move constructor and assignment operator
    Grid(Grid&& src) = default;
    Grid& operator=(Grid&& rhs) = default;

    std::optional<T>& at(size_t x, size_t y);
    const std::optional<T>& at(size_t x, size_t y) const;

    size_t getHeight() const { return m_height; }
    size_t getWidth()  const { return m_width; }

    void display() const;

    static const size_t DefaultWidth { 10 };
    static const size_t DefaultHeight { 10 };

private:
    void verifyCoordinate(size_t x, size_t y) const;

    std::vector<std::vector<std::optional<T>>> m_cells;
    size_t m_width {};
    size_t m_height {};
};


template <typename T>
Grid<T>::Grid(size_t width, size_t height)
    : m_width{width}
    , m_height{height}
{
    m_cells.resize(m_width);
    for(auto& column : m_cells) {
        column.resize(m_height);
    }
}

template <typename T>
void Grid<T>::verifyCoordinate(size_t x, size_t y) const
{
    if(x >= m_width) {
        throw std::out_of_range{ fmt::format("{} must be less than {}.", x, m_width) };
    }

    if(y >= m_height) {
        throw std::out_of_range{ fmt::format("{} must be less than {}.", y, m_height) };
    }
}

template <typename T>
const std::optional<T>& Grid<T>::at(size_t x, size_t y) const
{
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

template <typename T>
std::optional<T>& Grid<T>::at(size_t x, size_t y)
{
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

template <typename T>
void Grid<T>::display() const
{
    for(size_t i{}; i < m_width; ++i) {
        for(size_t j{}; j < m_height; ++j) {
            fmt::print("{:4}  ", at(i, j).value_or(0));
        }
        fmt::print("\n");
    }
    fmt::print("\n\n");
}

// const char* specialization of Grid class
template <>
class Grid<const char*>
{
public:
    explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);
    virtual ~Grid() = default;

    Grid(const Grid& src) = default;
    Grid& operator=(const Grid& rhs) = default;

    Grid(Grid&& src) = default;
    Grid& operator=(Grid&& rhs) = default;

    std::optional<std::string>& at(size_t x, size_t y);
    const std::optional<std::string>& at(size_t x, size_t y) const;

    size_t getHeight() const { return m_height; }
    size_t getWidth() const { return m_width; }

    void display() const;

    static const size_t DefaultWidth{10};
    static const size_t DefaultHeight{10};

private:
    void verifyCoordinate(size_t x, size_t y) const;

    std::vector<std::vector<std::optional<std::string>>> m_cells;
    size_t m_width{};
    size_t m_height{};
};

Grid<const char*>::Grid(size_t width, size_t height)
    : m_width{width}
    , m_height{height}
{
    m_cells.resize(m_width);
    for(auto& col : m_cells) {
        col.resize(m_height);
    }
}

void Grid<const char*>::verifyCoordinate(size_t x, size_t y) const
{
    if(x >= m_width) {
        throw std::out_of_range{ fmt::format("{} must be less than {}.\n", x, m_width)};
    }

    if(y >= m_height) {
        throw std::out_of_range{ fmt::format("{} must be less than {}.\n", y, m_height)};
    }
}

const std::optional<std::string>& Grid<const char*>::at(size_t x, size_t y) const
{
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

std::optional<std::string>& Grid<const char*>::at(size_t x, size_t y)
{
    return const_cast<std::optional<std::string>&>(std::as_const(*this).at(x, y));
}

void Grid<const char*>::display() const
{
    for(size_t i{}; i < m_width; ++i) {
        for(size_t j{}; j < m_height; ++j) {
            fmt::print("{:^8}  ", at(i, j).value_or(".."));
        }
        fmt::print("\n");
    }
    fmt::print("\n\n");
}